#include "pessoa.h"
#include "unity.h"

pessoa p;

void setUp(void){
    p = criarPessoa("123.456.789-10", "Murilo", "Prevelato", 'M', "26/04/2007");
}

void tearDown(void){
    liberarPessoa(p);
}

void teste_criarPessoa(){
    TEST_ASSERT_NOT_NULL(p);
    TEST_ASSERT_EQUAL_INT(0, getNumeroPessoa(p));
    TEST_ASSERT_EQUAL_INT(0, getMoradorPessoa(p));
}

void teste_getCpfPessoa(){
    TEST_ASSERT_EQUAL_STRING("123.456.789-10", getCpfPessoa(p));
}

void teste_getNomePessoa(){
    TEST_ASSERT_EQUAL_STRING("Murilo", getNomePessoa(p));
}

void teste_getSobrenomePessoa(){
    TEST_ASSERT_EQUAL_STRING("Prevelato", getSobrenomePessoa(p));
}

void teste_getSexoPessoa(){
    TEST_ASSERT_EQUAL_CHAR('M', getSexoPessoa(p));
}

void teste_getNascimentoPessoa(){
    TEST_ASSERT_EQUAL_STRING("26/04/2007", getNascimentoPessoa(p));
}

void teste_setGetCepPessoa(){
    setCepPessoa(p, "123123");
    TEST_ASSERT_EQUAL_STRING("123123", getCepPessoa(p));
}

void teste_setGetFacePessoa(){
    setFacePessoa(p, 'N');
    TEST_ASSERT_EQUAL_CHAR('N', getFacePessoa(p));
}

void teste_setGetNumeroPessoa(){
    setNumeroPessoa(p, 1);
    TEST_ASSERT_EQUAL_INT(1, getNumeroPessoa(p));
}

void teste_setGetComplementoPessoa(){
    setComplementoPessoa(p, "Bloco 2");
    TEST_ASSERT_EQUAL_STRING("Bloco 2", getComplementoPessoa(p));
}

void teste_setGetMoradorPessoa(){
    setMoradorPessoa(p, 1);
    TEST_ASSERT_EQUAL_INT(1, getMoradorPessoa(p));
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_criarPessoa);
    RUN_TEST(teste_getCpfPessoa);
    RUN_TEST(teste_getNomePessoa);
    RUN_TEST(teste_getSobrenomePessoa);
    RUN_TEST(teste_getSexoPessoa);
    RUN_TEST(teste_getNascimentoPessoa);
    RUN_TEST(teste_setGetCepPessoa);
    RUN_TEST(teste_setGetFacePessoa);
    RUN_TEST(teste_setGetNumeroPessoa);
    RUN_TEST(teste_setGetComplementoPessoa);
    RUN_TEST(teste_setGetMoradorPessoa);

    return UNITY_END();
}