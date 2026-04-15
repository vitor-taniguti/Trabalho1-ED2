#ifndef QRY_H
#define QRY_H

#include "txt.h"
#include "svg.h"
#include "hashfile.h"
#include "estatistica.h"
#include <stdio.h>

/*
Módulo responsável por ler o arquivo qry e executar os comandos correspondentes.
Os comandos lidos acarretam em mudanças nos habitantes e nas quadras da cidade.
*/

/// @brief Abre o arquivo para leitura
/// @param qry Ponteiro para o arquivo que será aberto
/// @param caminhoQry Caminho para o arquivo que será aberto
void abrirArquivoQry(arquivo *qry, char *caminhoQry);

/// @brief Remove a quadra identificada pelo cep e despeja todos os habitantes dela
/// @param cep Identificador da quadra
/// @param habitantes Hash file dos habitantes
/// @param quadras Hash file das quadras
/// @param txt Arquivo txt
/// @param svg Arquivo svg
void rq(char* cep, hash habitantes, hash quadras, arquivo txt, arquivo svg);

/// @brief Pega a quantidade de moradores em determinada quadra
/// @param cep Identificador da quadra
/// @param habitantes Hash file dos habitantes 
/// @param quadras Hash file das quadras
/// @param svg Arquivo svg
void pq(char* cep, hash habitantes, hash quadras, arquivo svg);

/// @brief Calcula e printa o censo de Bitnópolis no txt
/// @param e Estatística responsável pelo censo
/// @param txt Arquivo txt onde o censo será printado
void censo(estatistica e, arquivo txt);

/// @brief Pega as informações de determinado habitante
/// @param cpf Identificador de habitante
/// @param habitantes Hash file dos habitantes 
/// @param txt Arquivo txt
void h(char* cpf, hash habitantes, arquivo txt);

/// @brief Cria um habitante com os atributos especificados
/// @param cpf Identificador do habitante
/// @param nome Nome do habitante
/// @param sobrenome Sobrenome do habitante
/// @param sexo Sexo do habitante
/// @param nascimento Data de nascimento do habitante
/// @param habitantes Hash file dos habitantes 
/// @param e Estatísica que será alterada
void nasc(char* cpf, char* nome, char* sobrenome, char sexo, char* nascimento, hash habitantes, estatistica e);

/// @brief Habitante falece
/// @param cpf Identificador único do habitante
/// @param habitantes Hash file dos habitantes 
/// @param quadras Hash file das quadras
/// @param e Estatística que será alterada
/// @param txt Arquivo txt
/// @param svg Arquivo svg
void rip(char* cpf, hash habitantes, hash quadras, estatistica e, arquivo txt, arquivo svg);

/// @brief Habitante se muda para novo endereço
/// @param cpf Identificador único do habitante
/// @param cep Identificador único da quadra onde mudará
/// @param lado Lado da quadra onde mudará
/// @param numero Número do endereço onde mudará
/// @param complemento Complemento do endereço onde mudará
/// @param habitantes Hash file dos habitantes 
/// @param quadras Hash file das quadras
/// @param e Estatística que será alterada
/// @param svg Arquivo svg
void mud(char* cpf, char* cep, char lado, int numero, char* complemento, hash habitantes, hash quadras, estatistica e, arquivo svg);

/// @brief Despeja um morador de seu endereço
/// @param cpf Identificaro único de habitante
/// @param habitantes Hash file dos habitantes 
/// @param quadras Hash file das quadras
/// @param e Estatística que será alterada
/// @param txt Arquivo txt
/// @param svg Arquivo svg
void dspj(char* cpf, hash habitantes, hash quadras, estatistica e, arquivo txt, arquivo svg);

/// @brief Lê e processa as linhas de um arquivo de entrada
/// @param qry Ponteiro para o arquivo de entrada
/// @param txt Arquivo com extensao .txt que será usado
/// @param svg Aquivo com extensao .svg que será usado
/// @param habitantes Hashfile onde os habitantes estão armazenados
/// @param quadras Hashfile onde as quadras estão armazenadas
/// @param tq Tipo da quadra que será inserido no svg
/// @param e Estatística dos habitantes de Bitnópolis
void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, hash habitantes, hash quadras, tipoQuadra tq, estatistica e);

#endif