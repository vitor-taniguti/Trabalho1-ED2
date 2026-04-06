#include "geo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_cor 8
#define max_texto 1024

void abrirArquivoGeo(arquivo *geo, char *caminhoGeo){
    *geo = fopen(caminhoGeo, "r");
    if(*geo == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void processarLinha(char* linha, char* comando, hash quadras, tipoQuadra tq){
    char espessura[10] = {0}, corP[20] = {0}, corB[20] = {0}, tipo[3] = {0}, cep[20];
    double x = 0, y = 0, w = 0, h = 0;
    
    if (strcmp(comando, "cq") == 0){
        sscanf("%2s %s %s %s", tipo, espessura, corP, corB);
        setEspessuraTipoQuadra(tq, espessura);
        setCorPTipoQuadra(tq, corP);
        setCorBTipoQuadra(tq, corB);
    } else if (strcmp(comando, "q") == 0){
        sscanf("%2s %s %lf %lf %lf %lf", tipo, cep, &x, &y, &w, &h);
        inserirHash(quadras, criarQuadra(cep, x, y, w, h), cep);
    } else printf("Comando do geo inválido!\n");
}

void lerArquivoGeo(arquivo geo, hash quadras, tipoQuadra tq){
    if (geo == NULL){
        printf("O arquivo geo não foi aberto!\n");
        return;
    }

    char linha[256], comando[3];

    while (fgets(linha, sizeof(linha), geo)){
        int i = 0;
        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }
        comando[i] = '\0';
        processarLinha(linha, comando, quadras, tq);
    }
}