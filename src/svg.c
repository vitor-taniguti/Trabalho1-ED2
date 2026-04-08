#include "svg.h"
#include "quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivoSvg(arquivo *saida, char *caminhoSaida){
    *saida = fopen(caminhoSaida, "w");
    if (*saida == NULL){
        printf("Erro na abertura do arquivo!\n");
        exit(1);
    }
}

void inicializarSVG(arquivo saida){
    fprintf(saida, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void inserirRetanguloSVG(arquivo saida, double x, double y, double w, double h, char* corP, char* corB){
}

void inserirTextoSVG(arquivo saida, char* texto, double x, double y, char ancora){
    char *ancora_str;
    switch (ancora) {
        case 'm':
            ancora_str = "middle";
            break;
        case 'f':
            ancora_str = "end";
            break;
        case 'i':
        default: 
            ancora_str = "start";
            break;
    }

}

void fecharSVG(arquivo saida) {
    fprintf(saida, "</svg>\n");
}