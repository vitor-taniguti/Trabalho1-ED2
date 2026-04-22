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
/// @param pm Arquivo com extensão .pm que será lido
/// @param habitantes Hash dos habitantes
/// @param quadras Hash da quadras
/// @param e Estatística que será modificado ao ler o arquivo
void lerArquivoPm(arquivo pm, hash habitantes, hash quadras, estatistica e);

#endif