#ifndef TXT_H
#define TXT_H

#include <stdio.h>
#include <stdlib.h>
#include "pessoa.h"
#include "quadra.h"

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos com final .txt.
Os comentários feitos estão no padrão que o trabalho solicitou.
*/

typedef FILE* arquivo;

/// @brief Abre um arquivo de texto para gravação
/// @param txt Ponteiro duplo para o endereço do arquivo
/// @param caminhoTxt Ponteiro para o caminho onde será salvo o arquivo de texto
void abrirArquivoTxt(arquivo* txt, char* caminhoTxt);

/// @brief Printa a linha de comando lida no qry
/// @param txt Arquivo de texto onde a linha de comando será printada
/// @param linhaComando A linha de comando do qry
void printarLinhaComandoTxt(arquivo txt, char* linhaComando);

/// @brief Printa os dados da pessoa especificada
/// @param txt Arquivo de texto onde os dados serão printados
/// @param p Ponteiro para pessoa
void printarDadosPessoa(arquivo txt, pessoa p);

/// @brief Printa o endereco da pessoa
/// @param txt Arquivo de texto onde o endereço será printado
/// @param p Ponteiro para a pessoa
void printarEnderecoPessoa(arquivo txt, pessoa p);

/// @brief Printa o censo da cidade com as informações especificadas
/// @param txt Arquivo de texto onde o censo será printado
/// @param nHab Número total de habitantes
/// @param nMor Número total de moradores
/// @param morPhab Razão morador por habitante
/// @param nHom Número total de homens
/// @param nMul Número total de mulheres
/// @param pHabHom Porcentagem de habitantes homens
/// @param pHabMul Porcentagem de habitantes mulheres
/// @param pMorHom Porcentagem de moradores homens
/// @param pMorMul Porcentagem de moradores mulheres
/// @param nST Número total de pessoas sem teto
/// @param pSTHom Porcentagem de homens sem teto
/// @param pSTMul Porcentagem de mulheres sem teto
void printarCenso(arquivo txt, int nHab, int nMor, double morPhab, int nHom, int nMul, double pHabHom, double pHabMul, double pMorHom, double pMorMul, int nST, double pSTHom, double pSTMul);

#endif