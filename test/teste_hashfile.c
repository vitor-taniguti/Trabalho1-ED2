#include "hashfile.h"
#include "pessoa.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    FILE* arquivoHf;     
    FILE* arquivoHfd;    
} HashDinamicoMock;

hash teste;
elemento elementoPessoa;

void setUp(void){
    teste = criarHash("teste");
    elementoPessoa = criarPessoa("123.456.789-10", "Vitor", "Taniguti", 'M', "26/03/2007");
}

void tearDown(void){
    liberarHash(teste);
}

void teste_criarHash(){
    TEST_ASSERT_NOT_NULL(teste);
}

void teste_inserirHash_buscarHash(){
    char* cpf = getCpfPessoa(elementoPessoa);
    inserirHash(teste, elementoPessoa, cpf);

    elemento busca = buscarHash(teste, cpf);
    
    TEST_ASSERT_NOT_NULL(busca);
    TEST_ASSERT_EQUAL_STRING(cpf, getCpfPessoa(busca));
    
    free(busca);
}

void teste_removerHash(){
    char* cpf = getCpfPessoa(elementoPessoa);

    inserirHash(teste, elementoPessoa, cpf);

    removerHash(teste, cpf);

    elemento busca = buscarHash(teste, cpf);
    TEST_ASSERT_NULL(busca);
    
    if (busca != NULL) free(busca);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_criarHash);
    RUN_TEST(teste_inserirHash_buscarHash);
    RUN_TEST(teste_removerHash);

    return UNITY_END();
}