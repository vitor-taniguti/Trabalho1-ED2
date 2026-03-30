#include "svg.h"
#include "retangulo.h"
#include "texto.h"
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

void inserirRetanguloSVG(arquivo saida, retangulo r){
    fprintf(saida, "<rect id=\"%d\" style=\"fill:%s;fill-opacity:0.5;stroke:%s\" height=\"%lf\" width=\"%lf\" y=\"%lf\" x=\"%lf\" />\n", getIdRetangulo(r), getCorPRetangulo(r), getCorBRetangulo(r), getHRetangulo(r), getWRetangulo(r), getYRetangulo(r), getXRetangulo(r));
}

void inserirTextoSVG(arquivo saida, texto txt, tipoTexto tt){
    char *ancora_str;
    switch (getATexto(txt)) {
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
    fprintf(saida, "<text id=\"%d\" style=\"font-size:%s;font-family:%s;fill:%s;stroke:%s\" y=\"%lf\" x=\"%lf\" text-anchor=\"%s\">%s</text>\n", getIdTexto(txt), getSize(tt), getFamily(tt), getCorPTexto(txt), getCorBTexto(txt), getYtTexto(txt), getXtTexto(txt), ancora_str, getTxtoTexto(txt));
}

void fecharSVG(arquivo saida) {
    fprintf(saida, "</svg>\n");
}