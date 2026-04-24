#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashfile.h"
#include "quadra.h"

#define tamanho_bloco 2048
#define maximo_diretorio 1024
#define offset_table 46
#define offset_inicial_buckets 10000 

extern int getTamanhoPessoa();
extern int getTamanhoQuadra();

typedef struct{
    char chave[20];
    long offsetDados;
} Elemento;

#define max_registros_por_bucket ((tamanho_bloco - (2 * sizeof(int))) / sizeof(Elemento))

typedef struct{
    int profundidadeLocal;
    int quantidade;
    Elemento registros[max_registros_por_bucket];
} Bucket;

typedef struct{
    arquivo arquivoHf;     
    arquivo arquivoHfd;    

    int profundidadeGlobal;
    long diretorio[maximo_diretorio]; 
} Hash;

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

void imprimirDumpHash(hash h){      
    Hash* ha = (Hash*) h;

    fseek(ha->arquivoHfd, 0, SEEK_SET); 

    fprintf(ha->arquivoHfd, "\n*Dump table\n\n");
    int tamanhoDiretorio = 1 << ha->profundidadeGlobal;
    for (size_t i = 0; i < tamanhoDiretorio; i++){
        fprintf(ha->arquivoHfd, "[%d] %ld\n", i, ha->diretorio[i]);
    }

    fprintf(ha->arquivoHfd, "\n*Dump buckets\n");
    Bucket b;
    int indiceBloco = 0;

    long offsets_impressos[tamanhoDiretorio];
    int num_impressos = 0;

    int blocoLido = 1;

    for (int i = 0; i < tamanhoDiretorio; i++){
        long offsetAtual = ha->diretorio[i];
        int ja_impresso = 0;
        for (int k = 0; k < num_impressos; k++){
            if (offsets_impressos[k] == offsetAtual){
                ja_impresso = 1;
                break;
            }
        }

        if (!ja_impresso){
            Bucket b;
            fseek(ha->arquivoHf, offsetAtual, SEEK_SET);
            fread(&b, sizeof(Bucket), 1, ha->arquivoHf);

            fprintf(ha->arquivoHfd, "\nBucket %d\n\n", blocoLido);
            blocoLido++;

            for (size_t j = 0; j < max_registros_por_bucket; j++){
                if (j < b.quantidade){
                    fprintf(ha->arquivoHfd, "1 | %d______%s |\n", j, b.registros[j].chave);
                } else{
                    fprintf(ha->arquivoHfd, "0 | %d______ |\n", j);
                }
            }

            offsets_impressos[num_impressos] = offsetAtual;
            num_impressos++;
        }
    }
    
    fprintf(ha->arquivoHfd, "\nFIM DUMP");
    fflush(ha->arquivoHfd);
}

hash criarHash(char* nomeArquivo){
    Hash* h = malloc(sizeof(Hash));

    h->arquivoHf = fopen(nomeArquivo, "w+b");
    h->profundidadeGlobal = 0;
    
    for (int i = 0; i < maximo_diretorio; i++) h->diretorio[i] = i*sizeof(Bucket);

    Bucket b;
    memset(&b, 0, sizeof(Bucket));
    b.profundidadeLocal = 0;
    b.quantidade = 0;

    fseek(h->arquivoHf, 0, SEEK_SET);
    fwrite(&b, sizeof(Bucket), 1, h->arquivoHf);

    for (int i = 0; i < maximo_diretorio; i++) h->diretorio[i] = 0; 

    char nomeHfd[256];
    sprintf(nomeHfd, "%s.hfd", nomeArquivo);
    h->arquivoHfd = fopen(nomeHfd, "w");

    return (hash) h;
}

void inserirHash(hash h, elemento e, char* chave){
    Hash* ha = (Hash*) h; 

    int indice = funcaoHash(chave, ha->profundidadeGlobal);
    long offset = ha->diretorio[indice];

    fseek(ha->arquivoHf, offset, SEEK_SET);

    Bucket b;
    fread(&b, sizeof(Bucket), 1, ha->arquivoHf);

    if (b.quantidade < max_registros_por_bucket){
        fseek(ha->arquivoHf, 0, SEEK_END);
        long coordenadaElemento = ftell(ha->arquivoHf);
        int tamanho = getTamanhoElemento(chave);
        fwrite(e, tamanho, 1, ha->arquivoHf);

        strcpy(b.registros[b.quantidade].chave, chave);
        b.registros[b.quantidade].offsetDados = coordenadaElemento; 
        b.quantidade++;

        fseek(ha->arquivoHf, offset, SEEK_SET);

        if (fwrite(&b, sizeof(Bucket), 1, ha->arquivoHf)){
            // printf("Elemento com identificador %s inserido com sucesso!\n", chave);
        }
    } else{
        Elemento todos_registros[max_registros_por_bucket + 1];
        memset(todos_registros, 0, sizeof(Elemento) * (max_registros_por_bucket + 1));
        
        for (int i = 0; i < max_registros_por_bucket; i++){
            todos_registros[i] = b.registros[i];
        }

        fseek(ha->arquivoHf, 0, SEEK_END);
        long coordenadaElementoNovo = ftell(ha->arquivoHf);
        int tamanho = getTamanhoElemento(chave);
        fwrite(e, tamanho, 1, ha->arquivoHf);
        
        strcpy(todos_registros[max_registros_por_bucket].chave, chave);
        todos_registros[max_registros_por_bucket].offsetDados = coordenadaElementoNovo;

        int resolvido = 0;

        while (!resolvido){
            if (b.profundidadeLocal == ha->profundidadeGlobal){
                int tamanhoAntigo = 1 << ha->profundidadeGlobal; 
                for (int i = 0; i < tamanhoAntigo; i++){
                    ha->diretorio[i + tamanhoAntigo] = ha->diretorio[i];
                }
                ha->profundidadeGlobal++;
            }

            Bucket novo_balde;
            memset(&novo_balde, 0, sizeof(Bucket));
            
            b.quantidade = 0;
            b.profundidadeLocal++;
            novo_balde.profundidadeLocal = b.profundidadeLocal;

            fseek(ha->arquivoHf, 0, SEEK_END);
            long offset_novo_balde = ftell(ha->arquivoHf);
            fwrite(&novo_balde, sizeof(Bucket), 1, ha->arquivoHf); 

            for (int i = 0; i < max_registros_por_bucket + 1; i++){
                int novo_indice = funcaoHash(todos_registros[i].chave, b.profundidadeLocal);
                int bit_decisao = novo_indice & (1 << (b.profundidadeLocal - 1));
                
                if (bit_decisao == 0){
                    b.registros[b.quantidade] = todos_registros[i];
                    b.quantidade++;
                } else{
                    novo_balde.registros[novo_balde.quantidade] = todos_registros[i];
                    novo_balde.quantidade++;
                }
            }

            int mascara_decisao = 1 << (b.profundidadeLocal - 1); 
            int tamanhoDiretorio = 1 << ha->profundidadeGlobal;

            for (int i = 0; i < tamanhoDiretorio; i++){
                if (ha->diretorio[i] == offset){
                    if ((i & mascara_decisao) != 0){
                        ha->diretorio[i] = offset_novo_balde;
                    }
                }
            }

            if (b.quantidade <= max_registros_por_bucket && novo_balde.quantidade <= max_registros_por_bucket){
                fseek(ha->arquivoHf, offset, SEEK_SET);
                fwrite(&b, sizeof(Bucket), 1, ha->arquivoHf);

                fseek(ha->arquivoHf, offset_novo_balde, SEEK_SET);
                fwrite(&novo_balde, sizeof(Bucket), 1, ha->arquivoHf);
                
                resolvido = 1;
            } else{
                if (b.quantidade > max_registros_por_bucket){
                    fseek(ha->arquivoHf, offset_novo_balde, SEEK_SET);
                    fwrite(&novo_balde, sizeof(Bucket), 1, ha->arquivoHf);
                    
                    // O 'offset' de 'b' continua intacto. O loop vai girar e re-dividir ele.
                } else{
                    // O 'novo_balde' ficou lotado, e o 'b' ficou vazio com 0.
                    // Salvamos o 'b' vazio no disco.
                    fseek(ha->arquivoHf, offset, SEEK_SET);
                    fwrite(&b, sizeof(Bucket), 1, ha->arquivoHf);
                    
                    // O balde problemático que precisa ser re-dividido agora é o novo.
                    // Trocamos as variáveis para o laço funcionar com o novo balde na próxima rodada!
                    b = novo_balde;
                    offset = offset_novo_balde;
                }
            }
        }
    }
}

elemento buscarHash(hash h, char* chave){
    Hash* ha = (Hash*) h;

    int indice = funcaoHash(chave, ha->profundidadeGlobal);
    long offset = ha->diretorio[indice];
    fseek(ha->arquivoHf, offset, SEEK_SET);

    Bucket b;
    fread(&b, sizeof(Bucket), 1, ha->arquivoHf);

    for (int i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chave) == 0){
            fseek(ha->arquivoHf, b.registros[i].offsetDados, SEEK_SET);

            int tamanho = getTamanhoElemento(chave);
            elemento e = malloc(tamanho);
            
            fread(e, tamanho, 1, ha->arquivoHf);
            
            return e;
        }
    }

    return NULL;
}

void removerHash(hash h, char* chave){
    Hash* ha = (Hash*) h;

    int indice = funcaoHash(chave, ha->profundidadeGlobal);
    long offset = ha->diretorio[indice];
    
    fseek(ha->arquivoHf, offset, SEEK_SET);

    Bucket b;
    fread(&b, sizeof(Bucket), 1, ha->arquivoHf);

    for (int i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chave) == 0){
            for (int j = i; j < b.quantidade - 1; j++){
                b.registros[j] = b.registros[j + 1];
            }

            b.quantidade--;

            fseek(ha->arquivoHf, offset, SEEK_SET);

            fwrite(&b, sizeof(Bucket), 1, ha->arquivoHf);
            return; 
        }
    }
}

void atualizarHash(hash h, elemento e, char* chave){
    Hash* ha = (Hash*) h;

    int tamanho = getTamanhoElemento(chave);
    int indice = funcaoHash(chave, ha->profundidadeGlobal);
    long offset = ha->diretorio[indice];
    fseek(ha->arquivoHf, offset, SEEK_SET);

    Bucket b;
    fread(&b, sizeof(Bucket), 1, ha->arquivoHf);

    for (int i = 0; i < b.quantidade; i++){
        if (strcmp(b.registros[i].chave, chave) == 0){
            fseek(ha->arquivoHf, b.registros[i].offsetDados, SEEK_SET);
            fwrite(e, tamanho, 1, ha->arquivoHf);
        }
    }
}

void liberarHash(hash h){
    if (h == NULL){
        return; 
    }

    Hash *ha = (Hash*) h;

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

void percorrerHash(hash h, arquivo svgQry, FuncaoProcessamento processar, tipoQuadra tq){
    if (h == NULL) return;
    
    Hash *ha = (Hash*) h;
    int tamanhoDiretorio = 1 << ha->profundidadeGlobal;
    Bucket b;
    

    long offsetsVisitados[10000]; 
    int numVisitados = 0;

    int totalQuadrasDesenhadas = 0;

    for (size_t i = 0; i < tamanhoDiretorio; i++){
        long offsetAtual = ha->diretorio[i];

        int jaLido = 0;
        for (int v = 0; v < numVisitados; v++){
            if (offsetsVisitados[v] == offsetAtual){
                jaLido = 1;
                break;
            }
        }
        if (jaLido) continue;

        offsetsVisitados[numVisitados++] = offsetAtual;

        fseek(ha->arquivoHf, offsetAtual, SEEK_SET);
        fread(&b, sizeof(Bucket), 1, ha->arquivoHf);

        for (size_t j = 0; j < b.quantidade; j++){
            int tamanho = getTamanhoElemento(b.registros[j].chave);
            elemento e = malloc(tamanho);
            
            fseek(ha->arquivoHf, b.registros[j].offsetDados, SEEK_SET);
            fread(e, tamanho, 1, ha->arquivoHf);

            processar(svgQry, getXQuadra(e), getYQuadra(e), getWQuadra(e), getHQuadra(e), getCorPTipoQuadra(tq), getCorBTipoQuadra(tq));
            
            totalQuadrasDesenhadas++;
            free(e);
        }
    }
}