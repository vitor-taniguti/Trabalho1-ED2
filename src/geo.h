#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "texto.h"

/*
Módulo responsável por ler o arquivo de entrada .geo criar e inserir as formas na fila do chão.
A fila chão pode mudar conforme o programa é compilado
*/

typedef FILE* arquivo;
typedef void* fila;

/// @brief Abre o arquivo para leitura
/// @param geo Ponteiro para o arquivo que será aberto
/// @param caminhoGeo Caminho para o arquivo que será aberto
void abrirArquivoGeo(arquivo *geo, char *caminhoGeo);

/// @brief Lê e processa as linhas de um arquivop de entrada
/// @param geo Ponteiro para o arquivo de entrada
/// @param f Fila que as formas serão inseridas
/// @param tt Tipo do texto que será modificado
void lerArquivoGeo(arquivo geo, tabela t, tipoTexto tt);

#endif