#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include "quadra.h"

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos com final .svg.
A inserção das formas será feita no formato SVG padrão.
*/

typedef FILE *arquivo;
typedef void *forma;

/// @brief Cria o arquivo de saída SVG (.svg)
/// @param saida Ponteiro duplo para o endereço do arquivo
/// @param caminhoSaida Ponteiro com o nome do arquivo de saída criado
void abrirArquivoSvg(arquivo *saida, char *caminhoSaida);

/// @brief Adiciona a tag inicial do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
void inicializarSVG(arquivo saida);

/// @brief Adiciona a tag rect do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param 
void inserirRetanguloSVG(arquivo saida, double x, double y, double w, double h, char* corP, char* corB);

/// @brief 
/// @param saida 
/// @param x 
/// @param y 
/// @param raio 
/// @param corP 
/// @param corB 
void inserirCirculoSVG(arquivo saida, double x, double y, double raio, char* corP, char* corB);

/// @brief Adiciona a tag text do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param texto Texto que será escrito
void inserirTextoSVG(arquivo saida, char* texto, double x, double y, char ancora);

/// @brief 
/// @param saida 
/// @param x 
/// @param y 
void inserirXSVG(arquivo saida, double x, double y);

/// @brief 
/// @param saida 
/// @param x 
/// @param y 
void inserirCruzSVG(arquivo saida, double x, double y);

/// @brief Adiciona a tag final do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
void fecharSVG(arquivo saida);

#endif