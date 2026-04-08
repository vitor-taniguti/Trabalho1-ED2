#include "qry.h"
#include "pessoa.h"
#include "quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivoQry(arquivo *qry, char *caminhoQry){
    *qry = fopen(caminhoQry, "r");
    if(*qry == NULL){
        printf("Erro na abertura do arquivo qry!\n");
        exit(1);
    }
}

void rq(char* cep, hash habitantes, hash quadras, arquivo txt, arquivo svg){
    quadra q = buscarHash(quadras, cep);

    for (int i = 0; i < 4; i++){
        face f = getFaceQuadra(q, i);
        int qtdEnd = getQuantidadeEnderecosFace(f);

        for(int j = 0; j < qtdEnd; j++){
            endereco end = getEnderecoFace(f, j);
            int qtdMor = getQuantidadeMoradoresEndereco(end);

            for (int k = 0; k < qtdMor; k++){
                char* cpfMorador = getCpfEndereco(end, k);
                pessoa p = buscarHash(habitantes, cpfMorador);

                setMoradorPessoa(p, 0);
                printarDadosPessoa(txt, p);
            }
        }
    }

    inserirXSVG(svg, getXQuadra(q), getYQuadra(q));

    removerHash(quadras, cep);
}

void pq(char* cep, hash habitantes, hash quadras, arquivo svg){
    int faces[4] = {0, 0, 0, 0}, total = 0;
    char stringFaces[4][5], stringTotal[5];

    quadra q = buscarHash(quadras, cep);

    for (int i = 0; i < 4; i++){
        face f = getFaceQuadra(q, i);
        int qtdEnd = getQuantidadeEnderecosFace(f);

        for (int j = 0; j < qtdEnd; j++){
            endereco end = getEnderecoFace(f, j);
            int qtdMor = getQuantidadeMoradoresEndereco(end);

            faces[i] += qtdMor;
            total += qtdMor;
        }
    }

    for (int i = 0; i < 4; i++){
        snprintf(stringFaces[i], sizeof(stringFaces[i]), "%d", faces[i]);
    }
    snprintf(stringTotal, sizeof(stringTotal), "%d", total);

    double x = getXQuadra(q);
    double y = getYQuadra(q);
    double w = getWQuadra(q);
    double h = getHQuadra(q);

    inserirTextoSVG(svg, stringFaces[0], x+(w/2), y+h+5, 'm');
    inserirTextoSVG(svg, stringFaces[1], x+(w/2), y-5, 'm');
    inserirTextoSVG(svg, stringFaces[2], x, y+(h/2), 'f');
    inserirTextoSVG(svg, stringFaces[3], x+w, y+(h/2), 'i');
}

void processarLinha(char* linha, char* comando, hash habitantes, hash quadras, arquivo txt, arquivo svg){
    char cpf[15] = {0}, nome[50] = {0}, sobrenome[50] = {0}, sexo = ' ', nascimento[11] = {0};
    char cep[10] = {0}, complemento[10] = {0}, lado = ' ', tipo[2] = {0};
    int numero = 0;
    
    if (strcmp(comando, "rq") == 0){
        sscanf(linha, "%2s %9s", tipo, cep);
        rq(cep, habitantes, quadras, txt);
    } else if (strcmp(comando, "pq") == 0){

    } else if (strcmp(comando, "censo") == 0){

    } else if (strcmp(comando, "h?") == 0){

    } else if (strcmp(comando, "nasc") == 0){

    } else if (strcmp(comando, "rip") == 0){

    } else if (strcmp(comando, "mud") == 0){

    } else if (strcmp(comando, "dspj") == 0){

    } else printf("Comando do qry inválido!\n");
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, hash habitantes, hash quadras){
    if (qry == NULL){
        printf("O arquivo qry não foi aberto!\n");
        exit(1);
    }

    char linha[256], comando[6];

    while (fgets(linha, sizeof(linha), qry)){
        int i = 0;

        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }

        comando[i] = '\0';

        processarLinha(linha, comando, habitantes, quadras, txt, svg);
    }
}