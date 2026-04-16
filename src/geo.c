#include "geo.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivoGeo(arquivo *geo, char *caminhoGeo){
    *geo = fopen(caminhoGeo, "r");
    if(*geo == NULL){
        printf("Erro na abertura do arquivo geo!\n");
        exit(1);
    }
}

static void processarLinha(char* linha, char* comando, hash quadras, tipoQuadra tq, arquivo svg){
    char espessura[10] = {0}, corP[20] = {0}, corB[20] = {0}, tipo[3] = {0}, cep[20] = {0};
    double x = 0, y = 0, w = 0, h = 0;
    
    if (strcmp(comando, "cq") == 0){
        sscanf(linha, "%2s %9s %19s %19s", tipo, espessura, corP, corB);
        setEspessuraTipoQuadra(tq, espessura);
        setCorPTipoQuadra(tq, corP);
        setCorBTipoQuadra(tq, corB);
        
    } else if (strcmp(comando, "q") == 0){
        sscanf(linha, "%2s %19s %lf %lf %lf %lf", tipo, cep, &x, &y, &w, &h);

        quadra q = criarQuadra(cep, x, y, w, h);
        inserirHash(quadras, q, cep);

        inserirRetanguloSVG(svg, x, y, w, h, getCorPTipoQuadra(tq), getCorBTipoQuadra(tq));
        inserirTextoSVG(svg, cep, x+5, y+15, 'i');
        
        free(q);
    } else {
        printf("Comando do geo inválido: %s\n", comando);
    }
}

void lerArquivoGeo(arquivo geo, hash quadras, tipoQuadra tq, arquivo svg){
    if (geo == NULL){
        printf("O arquivo geo não foi aberto!\n");
        exit(1);
    }

    char linha[256], comando[3];

    while (fgets(linha, sizeof(linha), geo)){
        int i = 0;

        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') continue;

        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0' && i < 2){
            comando[i] = linha[i];
            i++;
        }

        comando[i] = '\0';

        processarLinha(linha, comando, quadras, tq, svg);
    }
}