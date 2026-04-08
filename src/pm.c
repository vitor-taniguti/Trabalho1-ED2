#include "pm.h"
#include "pessoa.h"
#include <stdlib.h>
#include <string.h>

void abrirArquivoPm(arquivo *pm, char *caminhoPm){
    *pm = fopen(caminhoPm, "r");
    if(*pm == NULL){
        printf("Erro na abertura do arquivo pm!\n");
        exit(1);
    }
}

void processarLinha(char* linha, char* comando, hash habitantes, estatistica e){
    char cpf[15] = {0}, nome[50] = {0}, sobrenome[50] = {0}, sexo = ' ', nascimento[11] = {0};
    char cep[10] = {0}, complemento[10] = {0}, face = ' ', tipo[2] = {0};
    int numero = 0;
    
    if (strcmp(comando, "p") == 0){
        sscanf(linha, "%1s %14s %s %s %c %10s", tipo, cpf, nome, sobrenome, sexo, nascimento);
        inserirHash(habitantes, criarPessoa(cpf, nome, sobrenome, sexo, nascimento), cpf);
    } else if (strcmp(comando, "m") == 0){
        sscanf(linha, "%1s %14s %9s %c %d %9s", tipo, cpf, cep, &face, &numero, complemento);
        pessoa p = buscarHash(habitantes, cpf);
        setCepPessoa(p, cep);
        setFacePessoa(p, face);
        setNumeroPessoa(p, numero);
        setComplementoPessoa(p, complemento);
    } else printf("Comando do pm inválido!\n");
}

void lerArquivoPm(arquivo pm, hash habitantes, estatistica e){
    if (pm == NULL){
        printf("O arquivo pm não foi aberto!\n");
        exit(1);
    }

    char linha[256], comando[2];

    while (fgets(linha, sizeof(linha), pm)){
        int i = 0;

        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }

        comando[i] = '\0';

        processarLinha(linha, comando, habitantes, e);
    }
}