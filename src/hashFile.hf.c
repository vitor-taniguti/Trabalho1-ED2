#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanhoBucket 4 
#define maximoDiretorio 1024 

typedef FILE* arquivo;

typedef struct{
    char chave[15];     
    long offsetDados;  
} EntradaIndice;

typedef struct{
    int profundidade_local;
    int quantidade;
    EntradaIndice registros[tamanhoBucket];
} BucketIndice;

typedef struct{
    int profundidadeGlobal;
    long offsetsBuckets[maximoDiretorio]; 
} Diretorio;

int funcaoHash(const char *chave, int profundidade){
    long hash = 5381;
    int c;
    while ((c = *chave++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash & ((1 << profundidade) - 1);
}

void inserirNoIndice(Diretorio *dir, arquivo arqHf, arquivo arqHfd, EntradaIndice novaEntrada){
    int indiceDir = funcaoHash(novaEntrada.chave, dir->profundidadeGlobal);
    long offsetBucket = dir->offsetsBuckets[indiceDir];

    BucketIndice b;
    fseek(arqHf, offsetBucket, SEEK_SET);
    fread(&b, sizeof(BucketIndice), 1, arqHf);

    if (b.quantidade < tamanhoBucket){
        b.registros[b.quantidade] = novaEntrada;
        b.quantidade++;
        fseek(arqHf, offsetBucket, SEEK_SET);
        fwrite(&b, sizeof(BucketIndice), 1, arqHf);
        return;
    }

    fprintf(arqHfd, "SPLIT: Bucket no offset %ld cheio. Chave causadora: %s\n", offsetBucket, novaEntrada.chave);

    BucketIndice novoB;
    novoB.quantidade = 0;
    novoB.profundidade_local = b.profundidade_local + 1;
    b.profundidade_local += 1;

    if (b.profundidade_local > dir->profundidadeGlobal){
        int tamanho_atual = 1 << dir->profundidadeGlobal;
        for (int i = 0; i < tamanho_atual; i++){
            dir->offsetsBuckets[i + tamanho_atual] = dir->offsetsBuckets[i];
        }
        dir->profundidadeGlobal++;
        fprintf(arqHfd, "DIRETORIO: Expansao para profundidade global %d\n", dir->profundidadeGlobal);
    }
 
    EntradaIndice todasEntradas[tamanhoBucket + 1];
    for(int i = 0; i < tamanhoBucket; i++) todasEntradas[i] = b.registros[i];
    todasEntradas[tamanhoBucket] = novaEntrada;

    b.quantidade = 0;

    fseek(arqHf, 0, SEEK_END);
    long novoOffset = ftell(arqHf);

    for (int i = 0; i < tamanhoBucket + 1; i++){
        int novo_hash = funcaoHash(todasEntradas[i].chave, b.profundidade_local);
  
        if (novo_hash == funcaoHash(todasEntradas[i].chave, dir->profundidadeGlobal)){
            b.registros[b.quantidade++] = todasEntradas[i];
        } else{
            novoB.registros[novoB.quantidade++] = todasEntradas[i];

            int numEntradasDir = 1 << dir->profundidadeGlobal;
            for(int j = 0; j < numEntradasDir; j++){
                if (funcaoHash(todasEntradas[i].chave, dir->profundidadeGlobal) == j){
                    dir->offsetsBuckets[j] = novoOffset;
                }
            }
        }
    }

    fseek(arqHf, offsetBucket, SEEK_SET);
    fwrite(&b, sizeof(BucketIndice), 1, arqHf);
    fseek(arqHf, novoOffset, SEEK_SET);
    fwrite(&novoB, sizeof(BucketIndice), 1, arqHf);
}

void removerDoIndice(Diretorio *dir, arquivo arqHf, const char *chaveRemover){
    int indiceDir = funcaoHash(chaveRemover, dir->profundidadeGlobal);
    long offsetBucket = dir->offsetsBuckets[indiceDir];

    BucketIndice b;
    fseek(arqHf, offsetBucket, SEEK_SET);
    fread(&b, sizeof(BucketIndice), 1, arqHf);

    int posicaoEcontrada = -1;
    for (int i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chaveRemover) == 0){
            posicaoEcontrada = i;
            break;
        }
    }

    if (posicaoEcontrada != -1){
        b.registros[posicaoEcontrada] = b.registros[b.quantidade - 1];

        b.quantidade--;

        fseek(arqHf, offsetBucket, SEEK_SET);
        fwrite(&b, sizeof(BucketIndice), 1, arqHf);
        
        printf("Chave %s removida com sucesso do indice.\n", chaveRemover);
    } else{
        printf("Chave %s nao encontrada para remocao.\n", chaveRemover);
    }
}