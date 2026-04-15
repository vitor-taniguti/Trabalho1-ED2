#include "txt.h"
#include "pessoa.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arquivo txtTeste;
pessoa pTeste;

void setUp(void){
    abrirArquivoTxt(&txtTeste, "teste.txt");
    pTeste = criarPessoa("12345678900", "Vitor", "Taniguti", 'M', "01-01-2000");
}

void tearDown(void){
    fclose(txtTeste);
    remove("teste.txt");
    free(pTeste);
}

void teste_abrirArquivoTxt(){
    arquivo f;
    abrirArquivoTxt(&f, "temp.txt");
    TEST_ASSERT_NOT_NULL(f);
    fclose(f);
    remove("temp.txt");
}

void teste_printarLinhaComandoTxt(){
    printarLinhaComandoTxt(txtTeste, "teste comando");
    fflush(txtTeste);

    FILE* f = fopen("teste.txt", "r");
    char buffer[200];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "[*] teste comando"));
    fclose(f);
}

void teste_printarDadosPessoa(){
    printarDadosPessoa(txtTeste, pTeste);
    fflush(txtTeste);

    FILE* f = fopen("teste.txt", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "Vitor"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "12345678900"));
    fclose(f);
}

void teste_printarEnderecoPessoa(){
    setCepPessoa(pTeste, "12345-000");
    setFacePessoa(pTeste, 'N');
    setNumeroPessoa(pTeste, 10);
    setComplementoPessoa(pTeste, "Apto1");
    setMoradorPessoa(pTeste, 1);

    printarEnderecoPessoa(txtTeste, pTeste);
    fflush(txtTeste);

    FILE* f = fopen("teste.txt", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "12345-000"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "Apto1"));
    fclose(f);
}

void teste_printarCenso(){
    printarCenso(txtTeste, 10, 8, 0.8, 5, 5, 50.0, 50.0, 60.0, 40.0, 2, 50.0, 50.0);
    fflush(txtTeste);

    FILE* f = fopen("teste.txt", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "Censo de Bitnópolis"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "Número de habitantes - 10"));
    fclose(f);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_abrirArquivoTxt);
    RUN_TEST(teste_printarLinhaComandoTxt);
    RUN_TEST(teste_printarDadosPessoa);
    RUN_TEST(teste_printarEnderecoPessoa);
    RUN_TEST(teste_printarCenso);

    return UNITY_END();
}