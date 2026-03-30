#include "txt.h"

void abrirArquivoTxt(arquivo *saida, char *caminhoTxt){
    *saida = fopen(caminhoTxt, "w");
    if (*saida == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
}