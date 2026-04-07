#include "qry.h"
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

void processarLinha(char* linha, char* comando, hash quadras, tipoQuadra tq){
    char cpf[15] = {0}, nome[50] = {0}, sobrenome[50] = {0}, sexo = ' ', nascimento[11] = {0};
    char cep[10] = {0}, complemento[10] = {0}, face = ' ', tipo[2] = {0};
    int numero = 0;
    
    if (strcmp(comando, "rq") == 0){
        
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

        processarLinha(linha, comando, quadras, tq);
    }
}