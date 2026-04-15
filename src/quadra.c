#include "quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximo_enderecos_quadra 50
#define maximo_pessoas_endereco 50

typedef struct{
    char corP[20], corB[20], espessura[10];
} TipoQuadra;

typedef struct{
    char cpfMoradores[maximo_pessoas_endereco][15];
    int quantidadeMoradores, numero;
} Endereco;

typedef struct{
    Endereco enderecos[maximo_enderecos_quadra];
    int quantidadeEnderecos;
} Face;

typedef struct{
    char cep[20];
    double x, y, w, h;
    Face faces[4];
} Quadra;

quadra criarQuadra(char* cep, double x, double y, double w, double h){
    Quadra* q = (Quadra*) malloc(sizeof(Quadra));

    strncpy(q->cep, cep, 19);
    q->cep[19] = '\0';

    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;

    for (int i = 0; i < 4; i++){
        q->faces[i].quantidadeEnderecos = 0;
    }

    return q;
}

int getTamanhoQuadra(){
    return sizeof(Quadra);
}

double getXQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->x;
}

double getYQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->y;
}

double getWQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->w;
}

double getHQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->h;
}

face getFaceQuadra(quadra q, int indice){
    Quadra* qua = (Quadra*) q;
    return &(qua->faces[indice]);
}

endereco getEnderecoFace(face f, int indice){
    Face* fa = (Face*) f;
    return &(fa->enderecos[indice]);
}

int getQuantidadeEnderecosFace(face f){
    Face* fa = (Face*) f;
    return fa->quantidadeEnderecos;
}

char* getCpfEndereco(endereco e, int indice){
    Endereco* end = (Endereco*) e;
    return end->cpfMoradores[indice];
}

int getQuantidadeMoradoresEndereco(endereco e){
    Endereco* end = (Endereco*) e;
    return end->quantidadeMoradores;
}

endereco buscarEndereco(quadra q, char face, int numero){
    Quadra* qua = (Quadra*) q;
    
    int faceInt;

    switch (face){
        case 'N': 
            faceInt = 0;
            break;
        case 'S':
            faceInt = 1;
            break;
        case 'L':
            faceInt = 2;
            break;
        case 'O':
            faceInt = 3;
            break;
        default:
            printf("Lado inválido ao buscar endereço\n");
            break;
    }

    for (int i = 0; i < qua->faces[faceInt].quantidadeEnderecos; i++){
        if (qua->faces[faceInt].enderecos[i].numero == numero) return &(qua->faces[face].enderecos[i]);
    }

    return NULL;
}

void adicionarMoradorEndereco(char* cpf, endereco e){
    Endereco* end = (Endereco*) e;
    int qtdMor = getQuantidadeMoradoresEndereco(end);

    if (qtdMor == maximo_pessoas_endereco){
        printf("Máximo de morador por endereço atingido!\n");
        return;
    }

    strncpy(end->cpfMoradores[qtdMor], cpf, 14);
    end->cpfMoradores[qtdMor][14] = '\0';

    end->quantidadeMoradores++;
}

void removerMoradorEndereco(char* cpf, endereco e){
    Endereco* end = (Endereco*) e;
    int qtdMor = getQuantidadeMoradoresEndereco(end), i = 0;

    while ((strcmp(end->cpfMoradores[i], cpf) != 0) && i < qtdMor) i++;

    if (i == qtdMor){
        printf("Morador no endereço não encontrado!\n");
        return;
    }

    strncpy(end->cpfMoradores[i], end->cpfMoradores[qtdMor-1], 14);
    end->cpfMoradores[i][14] = '\0';

    end->quantidadeMoradores--;
}

void getCoordenadasEndereco(quadra q, char face, int numero, double* x, double* y){
    *x = getXQuadra(q), *y = getYQuadra(q);
    double w = getWQuadra(q), h = getHQuadra(q);

    switch (face){
        case 'N': 
            *x += numero;
            *y += h;
            break;
        case 'S':
            *x += numero;
            break;
        case 'L':
            *y += numero;
            break;
        case 'O':
            *x += w;
            *y += numero;
            break;
        default:
            printf("Face inválida para pessoa!\n");
            return;
    }
}

void liberarQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    free(qua);
}

tipoQuadra criarTipoQuadra(){
    TipoQuadra* tq = malloc(sizeof(TipoQuadra));
    return (TipoQuadra*) tq;
}

char* getEspessuraTipoQuadra(tipoQuadra tq){
    TipoQuadra* qua = (TipoQuadra*) tq;
    return qua->espessura;
}

char* getCorBTipoQuadra(tipoQuadra tq){
    TipoQuadra* qua = (TipoQuadra*) tq;
    return qua->corB;
}   

char* getCorPTipoQuadra(tipoQuadra tq){
    TipoQuadra* qua = (TipoQuadra*) tq;
    return qua->corP;
}

void setEspessuraTipoQuadra(tipoQuadra tq, char* sw){
    TipoQuadra* qua = (TipoQuadra*) tq;
    
    strncpy(qua->espessura, sw, 9);
    qua->espessura[9] = '\0'; 
}

void setCorBTipoQuadra(tipoQuadra tq, char* cstrk){
    TipoQuadra* qua = (TipoQuadra*) tq;
    
    strncpy(qua->corB, cstrk, 9);
    qua->corB[9] = '\0';
}

void setCorPTipoQuadra(tipoQuadra tq, char* cfill){
    TipoQuadra* qua = (TipoQuadra*) tq;
    
    strncpy(qua->corP, cfill, 9);
    qua->corP[9] = '\0'; 
}

void liberarTipoQuadra(tipoQuadra tq){
    TipoQuadra* qua = (TipoQuadra*) tq;

    free(qua);
}