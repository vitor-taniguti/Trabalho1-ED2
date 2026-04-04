#include "quadra.h"
#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximo_enderecos_quadra 10

typedef struct{
    double numero;
    char complemento[10];
    char cpfMorador[15];
} Endereco;

typedef struct{
    Endereco enderecos[maximo_enderecos_quadra];
    int quantidadeEnderecos;
} Face;

typedef struct{
    char cep[10], corP[10], corB[10], espessura[10];
    double x, y, w, h;
    Face N, S, L, O;
} Quadra;

quadra criarQuadra(char* cep, double x, double y, double w, double h){
    Quadra* q = (Quadra*) malloc(sizeof(Quadra));

    strncpy(q->cep, cep, 9);
    q->cep[9] = '\0';

    q->x = x;
    q->y = y;
    q->w = w;
    q->h = h;

    q->N.quantidadeEnderecos = 0;
    q->S.quantidadeEnderecos = 0;
    q->L.quantidadeEnderecos = 0;
    q->O.quantidadeEnderecos = 0;

    return q;
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

char* getEspessuraQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->espessura;
}

char* getCorBQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->corB;
}   

char* getCorPQuadra(quadra q){
    Quadra* qua = (Quadra*) q;
    return qua->corP;
}

void setEspessuraQuadra(quadra q, char* sw){
    Quadra* qua = (Quadra*) q;
    
    strncpy(qua->espessura, sw, 9);
    qua->espessura[9] = '\0'; 
}

void setCorBQuadra(quadra q, char* cstrk){
    Quadra* qua = (Quadra*) q;
    
    strncpy(qua->corB, cstrk, 9);
    qua->corB[9] = '\0';
}

void setCorPQuadra(quadra q, char* cfill){
    Quadra* qua = (Quadra*) q;
    
    strncpy(qua->corP, cfill, 9);
    qua->corP[9] = '\0'; 
}