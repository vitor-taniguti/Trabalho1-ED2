#include "pessoa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char *cpf, *nome, *sobrenome, sexo, *nascimento;
    char *cep, *complemento, face, numero;
} Pessoa;

pessoa criarPessoa(char cpf, char* nome, char* sobrenome, char sexo, char* nascimento){
    Pessoa* p = (Pessoa*) malloc(sizeof(Pessoa));

    if (!p){
        printf("Falha na alocação de memória para criar uma pessoa!\n");
        return NULL;
    }

    p->cpf = cpf;

    p->nome = (char*) malloc(strlen(nome)+1);
    if (!p->nome){
        printf("Falha na alocação de memória no nome da pessoa!\n");
        return NULL;
    }
    strcpy(p->nome, nome);

    p->sobrenome = (char*) malloc(strlen(sobrenome)+1);
    if (!p->sobrenome){
        printf("Falha na alocação de memória no sobrenome da pessoa!\n");
        return NULL;
    }
    strcpy(p->sobrenome, sobrenome);

    p->sexo = sexo;

    p->nascimento = (char*) malloc(strlen(nascimento)+1);
    if (!p->nome){
        printf("Falha na alocação de memória na data de nascimento da pessoa!\n");
        return NULL;
    }
    strcpy(p->nascimento, nascimento);

    return p;
}

int getCpfPessoa(pessoa p){
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
    return pes->cpf;
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

void setCepPessoa(pessoa p, char* cep){
    Pessoa* pes = (Pessoa*) p;
    
    pes->cep = (char*) malloc(strlen(cep)+1);
    if (!pes->cep){
        printf("Falha na alocação de memória no CEP da pessoa!\n");
        return;
    }
    strcpy(pes->cep, cep);
}

void setFacePessoa(pessoa p, char face){
    Pessoa* pes = (Pessoa*) p;
    
    pes->face = (char*) malloc(strlen(face)+1);
    if (!pes->face){
        printf("Falha na alocação de memória no CEP da pessoa!\n");
        return;
    }
    strcpy(pes->face, face);
}

void setNumeroPessoa(pessoa p, int numero){
    Pessoa* pes = (Pessoa*) p;
    
    pes->numero = numero;
}

void setComplementoPessoa(pessoa p, char* complemento){
    Pessoa* pes = (Pessoa*) p;
    
    pes->complemento = (char*) malloc(strlen(complemento)+1);
    if (!pes->complemento){
        printf("Falha na alocação de memória no CEP da pessoa!\n");
        return;
    }
    strcpy(pes->complemento, complemento);
}