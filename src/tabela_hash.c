#include "tabela_hash.h"
#include <stdio.h>
#include <stdlib.h>

#define capacidade_inicial_tabela 2
#define capacidade_maxima_bucket 3

typedef struct{
    int tipo;
    elemento e;
} Conteudo;

typedef struct{
    int contador;
    Conteudo* vetor[capacidade_maxima_bucket];
} Bucket;

typedef struct{
    int tamanho;
    Bucket** buckets;
} Tabela;

tabela criarEInicializarTabela(){
    Tabela* t = malloc(sizeof(Tabela));
    if (!t) return NULL;

    t->tamanho = capacidade_inicial_tabela;
    t->buckets = malloc(t->tamanho * sizeof(Bucket*));

    for (int i = 0; i < t->tamanho; i++){
        t->buckets[i] = malloc(sizeof(Bucket));
        t->buckets[i]->contador = 0;
    }

    return (tabela)t;
}

int getTamanhoTabela(tabela t){
    Tabela* tab = (Tabela*) t;
    return tab->tamanho;
}

void liberarTabela(tabela t){
    Tabela* tab = (Tabela*) t;

    for (int i = 0; i < tab->tamanho; i++){
        for (int j = 0; j < tab->buckets[i]->contador; j++){
            free(tab->buckets[i]->vetor[j]);
        }
        free(tab->buckets[i]);
    }
    
    free(tab->buckets);
    free(tab);
}