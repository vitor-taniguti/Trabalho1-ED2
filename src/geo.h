#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include "hashfile.h"
#include "quadra.h"

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
void lerArquivoGeo(arquivo geo, hash quadras, tipoQuadra tq);

#endif