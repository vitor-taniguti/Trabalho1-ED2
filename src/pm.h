#ifndef PM_H
#define PM_H

#include "hashfile.h"
#include "estatistica.h"
#include <stdio.h>

typedef FILE* arquivo;

/// @brief Abre o arquivo com extensão .pm
/// @param saida Ponteiro duplo para o endereço do arquivo
/// @param caminhoPm Caminho onde será salvo o arquivo .pm
void abrirArquivoPm(arquivo* saida, char* caminhoPm);

/// @brief Lê o arquivo com extensão .pm e insere os objetos no arquivo correspondente
/// @param geo Arquivo que será lido
/// @param tabelaPm Arquivo da tabela hash reponsável para guardar os objetos lidos
void lerArquivoPm(arquivo pm, hash habitantes, estatistica e);

#endif