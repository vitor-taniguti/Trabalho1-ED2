#include "pm.h"
#include "pessoa.h"
#include "unity.h"
#include <stdlib.h>

hash habitantesTeste;
estatistica e;

void setUp(void){
    habitantesTeste = criarHash(100); 
    e = criarEstatistica();
}

void tearDown(void){
    remove("teste_saida.svg");
    remove("temporario.pm");
    liberarEstatistica(e);
    liberarHash(habitantesTeste);
}

void teste_abrirArquivoPm(){
    arquivo meuArquivo;

    arquivo temp = fopen("temporario.pm", "w");
    fprintf(temp, "arquivo de teste\n");
    fclose(temp);

    abrirArquivoPm(&meuArquivo, "temporario.pm");

    TEST_ASSERT_NOT_NULL(meuArquivo);

    fclose(meuArquivo);
}

void teste_lerArquivoPm(){
    arquivo leituraPm;

    arquivo temp = fopen("temporario.pm", "w");
    fprintf(temp, "p 123.456.789-10 Vitor Taniguti M 26/03/2007\n");
    fprintf(temp, "m 123.456.789-10 123123 N 10 Ap.1\n"); 
    fclose(temp);

    abrirArquivoPm(&leituraPm, "temporario.pm");

    lerArquivoPm(leituraPm, habitantesTeste, e);
    fclose(leituraPm);

    pessoa p = buscarHash(habitantesTeste, "123.456.789-10");

    TEST_ASSERT_NOT_NULL(p);

    TEST_ASSERT_EQUAL_STRING("123.456.789-10", getCpfPessoa(p));
    TEST_ASSERT_EQUAL_STRING("Vitor", getNomePessoa(p));
    TEST_ASSERT_EQUAL_STRING("Taniguti", getSobrenomePessoa(p));
    TEST_ASSERT_EQUAL_CHAR('M', getSexoPessoa(p));
    TEST_ASSERT_EQUAL_STRING("123123", getCepPessoa(p));
    TEST_ASSERT_EQUAL_CHAR('N', getFacePessoa(p));
    TEST_ASSERT_EQUAL_INT(10, getNumeroPessoa(p));
    TEST_ASSERT_EQUAL_STRING("Ap.1", getComplementoPessoa(p));
    
    free(p);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_abrirArquivoPm);
    RUN_TEST(teste_lerArquivoPm);

    return UNITY_END();
}