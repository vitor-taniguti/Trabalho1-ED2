#include "quadra.h"
#include "pessoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maximo_enderecos_quadra 50

typedef struct{
    char corP[20], corB[20], espessura[10];
} TipoQuadra;

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