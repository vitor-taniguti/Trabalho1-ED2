#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfile.h"

#define tamanho_bloco 2048
#define maximo_diretorio 1024
#define offset_table 46
#define offset_inicial_buckets 10000 

extern int getTamanhoPessoa();
extern int getTamanhoQuadra();

typedef struct{
    char chave[20];
    long offsetDados;
} EntradaIndice;

#define max_registros_por_bloco ((tamanho_bloco - (2 * sizeof(int))) / sizeof(EntradaIndice))

typedef struct{
    int profundidadeLocal;
    int quantidade;
    EntradaIndice registros[max_registros_por_bloco];
} BucketIndice;

typedef struct{
    arquivo arquivoHf;     
    arquivo arquivoHfd;    

    int numBuckets;
    int sizeRecord;
    int sizeBlock;
    int offsetKey;
    int sizeKey;
    int offsetTable;
    int offsetBuckets;
    int offsetOverflow;

    int profundidadeGlobal;
    long diretorio[maximo_diretorio]; 
} HashDinamico;

int getTamanhoElemento(char* chave){
    if (strlen(chave) > 10) return getTamanhoPessoa(); 
    else return getTamanhoQuadra(); 
}

int funcaoHash(const char *chave, int profundidade){
    long hash = 5381;
    int c;
    while ((c = *chave++)) hash = ((hash << 5) + hash) + c;
    if (profundidade == 0) return 0;
    return hash & ((1 << profundidade) - 1);
}

void salvarCabecalhoEDiretorio(HashDinamico *ha){
    fseek(ha->arquivoHf, 0, SEEK_SET);
    
    fwrite(&ha->numBuckets, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->sizeRecord, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->sizeBlock, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->offsetKey, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->sizeKey, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->offsetTable, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->offsetBuckets, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->offsetOverflow, sizeof(int), 1, ha->arquivoHf);
    fwrite(&ha->profundidadeGlobal, sizeof(int), 1, ha->arquivoHf);

    fseek(ha->arquivoHf, offset_table, SEEK_SET);
    int tamanhoAtual = 1 << ha->profundidadeGlobal;
    fwrite(ha->diretorio, sizeof(long), tamanhoAtual, ha->arquivoHf);
    fflush(ha->arquivoHf);
}

void gerarDumpHfd(HashDinamico *ha){
    fseek(ha->arquivoHfd, 0, SEEK_SET); 
    
    fprintf(ha->arquivoHfd, "DUMP\n");
    fprintf(ha->arquivoHfd, "*Dump cabecalho\n");
    fprintf(ha->arquivoHfd, "numBucketsd %d \n", ha->numBuckets);
    fprintf(ha->arquivoHfd, "sizeRecordd %d \n", ha->sizeRecord);
    fprintf(ha->arquivoHfd, "sizeBlock %d \n", ha->sizeBlock);
    fprintf(ha->arquivoHfd, "offsetKey %d \n", ha->offsetKey);
    fprintf(ha->arquivoHfd, "sizeKey %d \n", ha->sizeKey);
    fprintf(ha->arquivoHfd, "offsetTable %d \n", ha->offsetTable);
    fprintf(ha->arquivoHfd, "offsetBuckets %d \n", ha->offsetBuckets);
    fprintf(ha->arquivoHfd, "offsetOverflow %d\n", ha->offsetOverflow);

    fprintf(ha->arquivoHfd, "* Dump table\n");
    int tamanhoDiretorio = 1 << ha->profundidadeGlobal;
    for (size_t i = 0; i < tamanhoDiretorio; i++){
        fprintf(ha->arquivoHfd, "[%d] %ld\n", i, ha->diretorio[i]);
    }

    fprintf(ha->arquivoHfd, "*Dump buckets\n");
    BucketIndice b;
    int indiceBloco = 0;
    
    for (size_t i = 0; i < tamanhoDiretorio; i++){
        if (i > 0 && ha->diretorio[i] == ha->diretorio[i-1]) continue;

        fseek(ha->arquivoHf, ha->diretorio[i], SEEK_SET);
        fread(&b, sizeof(BucketIndice), 1, ha->arquivoHf);

        fprintf(ha->arquivoHfd, "BLOCO: %d\n", indiceBloco++);
        
        for (size_t j = 0; j < max_registros_por_bloco; j++){
            if (j < b.quantidade){
                fprintf(ha->arquivoHfd, "1 | 0000000000 | %d______%s | 0.000000 |\n", j, b.registros[j].chave);
            } else{
                fprintf(ha->arquivoHfd, "0 | 0000000000 | %d______ | 0.000000 |\n", j);
            }
        }
    }
    
    fprintf(ha->arquivoHfd, "FIM DUMP\n");
    fflush(ha->arquivoHfd);
}

hash criarHash(char* nomeArquivo){
    HashDinamico *ha = malloc(sizeof(HashDinamico));
    char nomeHf[50], nomeHfd[50];

    if (nomeArquivo != NULL){
        snprintf(nomeHf, sizeof(nomeHf), "%s.hf", nomeArquivo);
        snprintf(nomeHfd, sizeof(nomeHfd), "%s.hfd", nomeArquivo);
    } else return NULL;

    ha->arquivoHf = fopen(nomeHf, "wb+");
    ha->arquivoHfd = fopen(nomeHfd, "w");

    ha->numBuckets = 2;
    ha->sizeRecord = sizeof(EntradaIndice);
    ha->sizeBlock = tamanho_bloco;
    ha->offsetKey = 0;
    ha->sizeKey = 20;
    ha->offsetTable = offset_table;
    ha->offsetBuckets = offset_inicial_buckets;
    ha->offsetOverflow = -1;

    ha->profundidadeGlobal = 1;

    BucketIndice bVazio = {1, 0, {{0}}};
    
    fseek(ha->arquivoHf, ha->offsetBuckets, SEEK_SET);
    long offsetB0 = ftell(ha->arquivoHf);
    fwrite(&bVazio, sizeof(BucketIndice), 1, ha->arquivoHf);
    
    long offsetB1 = offsetB0 + tamanho_bloco;
    fseek(ha->arquivoHf, offsetB1, SEEK_SET);
    fwrite(&bVazio, sizeof(BucketIndice), 1, ha->arquivoHf);

    ha->diretorio[0] = offsetB0;
    ha->diretorio[1] = offsetB1;

    salvarCabecalhoEDiretorio(ha);
    gerarDumpHfd(ha);

    return (hash) ha;
}

void inserirHash(hash h, elemento e, char* chave){
    HashDinamico *ha = (HashDinamico*) h;
    
    int indiceDir = funcaoHash(chave, ha->profundidadeGlobal);
    long offsetBucket = ha->diretorio[indiceDir];

    BucketIndice b;
    fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
    fread(&b, sizeof(BucketIndice), 1, ha->arquivoHf);

    fseek(ha->arquivoHf, 0, SEEK_END);
    long offsetDosDados = ftell(ha->arquivoHf);
    int tamanho = getTamanhoElemento(chave);
    fwrite(e, tamanho, 1, ha->arquivoHf); 

    EntradaIndice novaEntrada;
    strncpy(novaEntrada.chave, chave, 19);
    novaEntrada.chave[19] = '\0';
    novaEntrada.offsetDados = offsetDosDados;

    if (b.quantidade < max_registros_por_bloco){
        b.registros[b.quantidade++] = novaEntrada;
        fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
        fwrite(&b, sizeof(BucketIndice), 1, ha->arquivoHf);
        gerarDumpHfd(ha);
        return;
    }

    BucketIndice novoB = {b.profundidadeLocal + 1, 0, {{0}}};
    b.profundidadeLocal += 1;

    if (b.profundidadeLocal > ha->profundidadeGlobal){
        int tamanho_atual = 1 << ha->profundidadeGlobal;
        for (size_t i = 0; i < tamanho_atual; i++) ha->diretorio[i + tamanho_atual] = ha->diretorio[i];
        ha->profundidadeGlobal++;
    }

    EntradaIndice todas[max_registros_por_bloco + 1];
    for(int i = 0; i < max_registros_por_bloco; i++) todas[i] = b.registros[i];
    todas[max_registros_por_bloco] = novaEntrada;

    b.quantidade = 0;

    fseek(ha->arquivoHf, 0, SEEK_END);
    long novoOffset = ftell(ha->arquivoHf);
    ha->numBuckets++;

    int bit_verificacao = 1 << (b.profundidadeLocal - 1);
    for (size_t i = 0; i < max_registros_por_bloco + 1; i++){
        int hashChave = funcaoHash(todas[i].chave, b.profundidadeLocal);
        if ((hashChave & bit_verificacao) == 0) b.registros[b.quantidade++] = todas[i];
        else novoB.registros[novoB.quantidade++] = todas[i];
    }

    int numEntradas = 1 << ha->profundidadeGlobal;
    int mascara_nova = (1 << b.profundidadeLocal) - 1;
    int hash_novo_bucket = funcaoHash(novoB.registros[0].chave, b.profundidadeLocal);

    for (size_t i = 0; i < numEntradas; i++){
        if (ha->diretorio[i] == offsetBucket && (i & mascara_nova) == hash_novo_bucket){
            ha->diretorio[i] = novoOffset;
        }
    }

    fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
    fwrite(&b, sizeof(BucketIndice), 1, ha->arquivoHf);
    fseek(ha->arquivoHf, novoOffset, SEEK_SET);
    fwrite(&novoB, sizeof(BucketIndice), 1, ha->arquivoHf);

    salvarCabecalhoEDiretorio(ha);
    gerarDumpHfd(ha);
}

elemento buscarHash(hash h, char* chave){
    HashDinamico *ha = (HashDinamico*) h;
    
    int indiceDir = funcaoHash(chave, ha->profundidadeGlobal);
    long offsetBucket = ha->diretorio[indiceDir];

    BucketIndice b;
    fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
    fread(&b, sizeof(BucketIndice), 1, ha->arquivoHf);

    for (size_t i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chave) == 0){
            int tamanho = getTamanhoElemento(chave);
            elemento e = malloc(tamanho);
            fseek(ha->arquivoHf, b.registros[i].offsetDados, SEEK_SET);
            fread(e, tamanho, 1, ha->arquivoHf);
            return e;
        }
    }
    return NULL;
}

void removerHash(hash h, char* chave){
    HashDinamico *ha = (HashDinamico*) h;
    
    int indiceDir = funcaoHash(chave, ha->profundidadeGlobal);
    long offsetBucket = ha->diretorio[indiceDir];

    BucketIndice b;
    fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
    fread(&b, sizeof(BucketIndice), 1, ha->arquivoHf);

    for (size_t i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chave) == 0){
            b.registros[i] = b.registros[b.quantidade - 1];
            b.quantidade--;

            fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
            fwrite(&b, sizeof(BucketIndice), 1, ha->arquivoHf);
            gerarDumpHfd(ha);
            return;
        }
    }
}

void atualizarHash(hash h, elemento e, char* chave){
    HashDinamico *ha = (HashDinamico*) h;

    int indiceDir = funcaoHash(chave, ha->profundidadeGlobal);
    long offsetBucket = ha->diretorio[indiceDir];

    BucketIndice b;
    fseek(ha->arquivoHf, offsetBucket, SEEK_SET);
    fread(&b, sizeof(BucketIndice), 1, ha->arquivoHf);

    for (size_t i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chave) == 0){
            long offsetDosDados = b.registros[i].offsetDados;
            int tamanho = getTamanhoElemento(chave);

            fseek(ha->arquivoHf, offsetDosDados, SEEK_SET);

            fwrite(e, tamanho, 1, ha->arquivoHf);

            fflush(ha->arquivoHf);
            return;
        }
    }
    
    printf("Erro: Tentativa de atualizar chave inexistente (%s)\n", chave);
}

void liberarHash(hash h){
    if (h == NULL){
        return; 
    }

    HashDinamico *ha = (HashDinamico*) h;

    if (ha->arquivoHf != NULL){
        fclose(ha->arquivoHf);
        ha->arquivoHf = NULL;
    }

    if (ha->arquivoHfd != NULL){
        fclose(ha->arquivoHfd);
        ha->arquivoHfd = NULL;
    }

    free(ha);
}