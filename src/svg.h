#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include <stdlib.h>
#include "quadra.h"

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos svg.
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
/// @param x Coordenada X da âncora do retângulo
/// @param y Coordenada Y da âncora do retângulo
/// @param w Largura do retângulo
/// @param h Altura do retângulo
/// @param corP Cor de preenchimento do retângulo
/// @param corB Cor de borda do retângulo
void inserirRetanguloSVG(arquivo saida, double x, double y, double w, double h, char* corP, char* corB);

/// @brief Adiciona a tag circle do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param x Coordenada X da âncora do círculo
/// @param y Coordenada Y da âncora do círculo
/// @param raio Raio do círculo
/// @param corP Cor de preenchimento do círculo
/// @param corB Cor de borda do círculo
void inserirCirculoSVG(arquivo saida, double x, double y, double raio, char* corP, char* corB);

/// @brief Adiciona a tag text do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param texto Texto que será escrito
void inserirTextoSVG(arquivo saida, char* texto, double x, double y, char ancora);

/// @brief Adiciona um formato de X no arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param x Coordenada X do X
/// @param y Coorenada Y do X
void inserirXSVG(arquivo saida, double x, double y);

/// @brief Adiciona uma cruz no arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
/// @param x Coordenada X da cruz
/// @param y Coordenada Y da cruz
/// @param cor Cor da cruz
void inserirCruzSVG(arquivo saida, double x, double y, char* cor);

/// @brief Adiciona a tag final do arquivo SVG
/// @param saida Ponteiro para o arquivo de saída
void fecharSVG(arquivo saida);

#endif