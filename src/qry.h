#ifndef QRY_H
#define QRY_H

#include "txt.h"
#include "svg.h"
#include "tabela_hash.h"
#include <stdio.h>

/*
Módulo responsável por ler o arquivo qry e executar os comandos correspondentes.
Os comandos lidos acarretam em mudanças nas formas da fila do chão
*/

/// @brief Abre o arquivo para leitura
/// @param qry Ponteiro para o arquivo que será aberto
/// @param caminhoQry Caminho para o arquivo que será aberto
void abrirArquivoQry(arquivo *qry, char *caminhoQry);

/// @brief Lê e processa as linhas de um arquivo de entrada
/// @param qry Ponteiro para o arquivo de entrada
/// @param txt Arquivo com extensao .txt que será usado
/// @param svg Aquivo com extensao .svg que será usado
void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, tabela t);

#endif