#ifndef TXT_H
#define TXT_H

#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"
#include "texto.h"

/*
Módulo responsável por gerenciar a criação e escrita dos arquivos com final .txt.
Os comentários feitos estão no padrão que o trabalho solicitou.
*/

typedef FILE* arquivo;
typedef void* Forma;

/// @brief Abre um arquivo de texto para gravação
/// @param txt Ponteiri duplo para o endereço do arquivo
/// @param caminhoTxt Ponteiro para o caminho onde será salvo o arquivo de texto
void abrirArquivoTxt(arquivo *txt, char *caminhoTxt);

#endif