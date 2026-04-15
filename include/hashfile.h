#ifndef HASHFILE_H
#define HASHFILE_H

#include "quadra.h"
#include <stdio.h>

/*
Módulo responsável pelo gerenciamento do hashfile. 
Esse módulo consegue diferenciar quando a chave passada é cpf e cep, assim, inserindo corretamente com o tamanho certo de bits no disco.
Contém as funções de inserir, buscar e remover do hashfile.
Além disso, cria um dump (arquivo hfd) reportando suas modificações.
*/

typedef void* hash;
typedef void* elemento;
typedef FILE* arquivo;
typedef void (*FuncaoProcessamento)(arquivo svgQry, double x, double y, double w, double h, char* corP, char* corB);

/// @brief Cria um hashfile extensível (dinâmico)
/// @param nomeArquivo Nome do arquivo do hashfile
/// @return O hashfile criado
hash criarHash(char* nomeArquivo);

/// @brief Inserir o elemento do hashfile (habitante ou quadra)
/// @param h Hashfile onde o elemento será inserido
/// @param e Elemento que será inserido
/// @param chave Chave responsável pelo espalhamento da função hash (cpf para habitantes, cep para quadras)
void inserirHash(hash h, elemento e, char* chave);

/// @brief Busca o elemento do hashfile (habitante ou quadra)
/// @param h Hashfile onde o elemento será buscado
/// @param chave Chave responsável por facilitar a busca 
/// @return O elemento buscado ou NULL se não for encontrado
elemento buscarHash(hash h, char* chave);

/// @brief Remove o elemento do hashfile (habitante ou quadra)
/// @param h Hashfile onde o elemento será removido
/// @param chave Chave responsável por buscar o elemento que será removido
void removerHash(hash h, char* chave);

/// @brief Atualiza o registro do elemento no disco 
/// @param h Hashfile onde o elemento se encontra
/// @param e Elemento que será atualizado
/// @param chave Chave responsável por buscar o elemento que será atualizado
void atualizarHash(hash h, elemento e, char* chave);

/// @brief Libera os arquivos do disco do hashfile
/// @param h Hashfile que será liberado
void liberarHash(hash h);

/// @brief Percorre o hash e realiza a função passada no loop
/// @param h Hash que será percorrido
/// @param svgQry Arquivo onde será inserido as quadras
/// @param processar Função que será executada
/// @param tq Tipo da quadra que será inserida
void percorrerHash(hash h, arquivo svgQry, FuncaoProcessamento processar, tipoQuadra tq);

/// @brief Imprime o dump do hash file (.hfd)
/// @param h Hash file que o dump será impresso
void imprimirDumpHash(hash h);

#endif