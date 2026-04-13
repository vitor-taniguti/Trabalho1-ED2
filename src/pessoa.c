#include "pessoa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char cpf[15], nome[50], sobrenome[50], sexo, nascimento[11];
    char cep[10], complemento[10], face;
    int numero, morador;
} Pessoa;

pessoa criarPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* nascimento){
    Pessoa* p = (Pessoa*) malloc(sizeof(Pessoa));

    if (!p){
        printf("Falha na alocação de memória para criar uma pessoa!\n");
        return NULL;
    }

    if (nome != NULL){
        strncpy(p->cpf, cpf, 14);
        p->cpf[14] = '\0';
    } else return NULL;


        strncpy(p->nome, nome, 49);
        p->nome[49] = '\0';

    strncpy(p->sobrenome, sobrenome, 49);
    p->sobrenome[49] = '\0';

    p->sexo = sexo;

    strncpy(p->nascimento, nascimento, 10);
    p->nascimento[10] = '\0';

    p->numero = 0;

    p->morador = 0;

    return p;
}

int getTamanhoPessoa(){
    return sizeof(Pessoa);
}

char* getCpfPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->cpf;
}

char* getNomePessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->nome;
}

char* getSobrenomePessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->sobrenome;
}

char getSexoPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->sexo;
}

char* getNascimentoPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->nascimento;
}

char* getCepPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->cep;
}

char getFacePessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->face;
}

int getNumeroPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->numero;
}

char* getComplementoPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->complemento;
}

int getMoradorPessoa(pessoa p){
    Pessoa* pes = (Pessoa*) p;
    return pes->morador;
}

void setCepPessoa(pessoa p, char* cep){
    Pessoa* pes = (Pessoa*) p;
    
    strncpy(pes->cep, cep, 9);
    pes->cep[9] = '\0';
}

void setFacePessoa(pessoa p, char face){
    Pessoa* pes = (Pessoa*) p;
    
    pes->face = face;
}

void setNumeroPessoa(pessoa p, int numero){
    Pessoa* pes = (Pessoa*) p;
    
    pes->numero = numero;
}

void setComplementoPessoa(pessoa p, char* complemento){
    Pessoa* pes = (Pessoa*) p;
    
    strncpy(pes->complemento, complemento, 9);
    pes->complemento[9] = '\0';
}

void setMoradorPessoa(pessoa p, int morador){
    Pessoa* pes = (Pessoa*) p;
    pes->morador = morador;
}

void liberarPessoa(pessoa p){
    free(p);
}