#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "hashfile.h"
#include "quadra.h"

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos geo.
A leitura do arquivo, além de, claro, ler, também insere no arquivo .svg as quadras lidas, com as especificações também lidas no arquivo.
Esse módulo é responsável pela criação da cidade (abstração).
*/

typedef FILE* arquivo;
typedef void* fila;

/// @brief Abre o arquivo para leitura
/// @param geo Ponteiro para o arquivo que será aberto
/// @param caminhoGeo Caminho para o arquivo que será aberto
void abrirArquivoGeo(arquivo *geo, char *caminhoGeo);

/// @brief Lê e processa as linhas de um arquivop de entrada
/// @param geo Ponteiro para o arquivo de entrada
/// @param quadras Hashfile onde as quadras serão inseridas
/// @param tq Tipo das quadras (espessua, cor de preenchimento e de borda)
/// @param svg Ponteiro para a arquivo com final .svg
void lerArquivoGeo(arquivo geo, hash quadras, tipoQuadra tq, arquivo svg);

#endif