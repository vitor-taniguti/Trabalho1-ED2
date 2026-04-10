#ifndef PM_H
#define PM_H

#include "hashfile.h"
#include "estatistica.h"
#include <stdio.h>

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos pm.
A leitura do arquivo resulta na criação dos habitantes de Bitnópolis, com seus atributos já especificados.
Além disso, a leitura promove os habitantes à moradores, concedendo a eles os atributos de morador.
Por fim, também atualiza a estatística dos habitantes de Bitnópolis. 
Esse módulo é responsável pela povoação da cidade (abstração).
*/

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