#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivoSvg(arquivo *saida, char *caminhoSaida){
    *saida = fopen(caminhoSaida, "w");
    if (*saida == NULL){
        printf("Erro na abertura do arquivo SVG: %s\n", caminhoSaida);
        exit(1);
    }
}

void inicializarSVG(arquivo saida){
    fprintf(saida, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}

void inserirRetanguloSVG(arquivo saida, double x, double y, double w, double h, char* corP, char* corB){
    fprintf(saida, "\t<rect x=\"%.4f\" y=\"%.4f\" width=\"%.4f\" height=\"%.4f\" fill=\"%s\" stroke=\"%s\" />\n", x, y, w, h, corP, corB);
}

void inserirCirculoSVG(arquivo saida, double x, double y, double raio, char* corP, char* corB){
    fprintf(saida, "\t<circle cx=\"%.4f\" cy=\"%.4f\" r=\"%.4f\" fill=\"%s\" stroke=\"%s\" />\n", x, y, raio, corP, corB);
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

    fprintf(saida, "\t<text x=\"%.4f\" y=\"%.4f\" text-anchor=\"%s\">%s</text>\n", x, y, ancora_str, texto);
}

void inserirXSVG(arquivo saida, double x, double y){
    fprintf(saida, "\t<line x1=\"%.4f\" y1=\"%.4f\" x2=\"%.4f\" y2=\"%.4f\" stroke=\"black\" stroke-width=\"2\" />\n", x - 5.0, y - 5.0, x + 5.0, y + 5.0);
    fprintf(saida, "\t<line x1=\"%.4f\" y1=\"%.4f\" x2=\"%.4f\" y2=\"%.4f\" stroke=\"black\" stroke-width=\"2\" />\n", x - 5.0, y + 5.0, x + 5.0, y - 5.0);
}

void inserirCruzSVG(arquivo saida, double x, double y, char* cor){
    fprintf(saida, "\t<line x1=\"%.4f\" y1=\"%.4f\" x2=\"%.4f\" y2=\"%.4f\" stroke=\"%s\" stroke-width=\"2\" />\n", x, y - 8.0, x, y + 12.0, cor);
    fprintf(saida, "\t<line x1=\"%.4f\" y1=\"%.4f\" x2=\"%.4f\" y2=\"%.4f\" stroke=\"%s\" stroke-width=\"2\" />\n", x - 6.0, y - 2.0, x + 6.0, y - 2.0, cor);
}

void fecharSVG(arquivo saida) {
    fprintf(saida, "</svg>\n");
}