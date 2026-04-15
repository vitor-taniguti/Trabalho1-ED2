#include "quadra.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

quadra qTeste;
tipoQuadra tqTeste;

void setUp(void){
    qTeste = criarQuadra("12345-000", 10.0, 20.0, 100.0, 50.0);
    tqTeste = criarTipoQuadra();
}

void tearDown(void){
    liberarQuadra(qTeste);
    liberarTipoQuadra(tqTeste);
}

void teste_criarQuadra(){
    TEST_ASSERT_NOT_NULL(qTeste);
}

void teste_gettersQuadra(){
    TEST_ASSERT_EQUAL_DOUBLE(10.0, getXQuadra(qTeste));
    TEST_ASSERT_EQUAL_DOUBLE(20.0, getYQuadra(qTeste));
    TEST_ASSERT_EQUAL_DOUBLE(100.0, getWQuadra(qTeste));
    TEST_ASSERT_EQUAL_DOUBLE(50.0, getHQuadra(qTeste));
}

void teste_facesInicialmenteVazias(){
    for(int i = 0; i < 4; i++){
        face f = getFaceQuadra(qTeste, i);
        TEST_ASSERT_EQUAL_INT(0, getQuantidadeEnderecosFace(f));
    }
}
void teste_adicionarMorador(){
    face f = getFaceQuadra(qTeste, 0);

    endereco e = getEnderecoFace(f, 0);

    adicionarMoradorEndereco("111", e);

    TEST_ASSERT_EQUAL_INT(1, getQuantidadeMoradoresEndereco(e));
    TEST_ASSERT_EQUAL_STRING("111", getCpfEndereco(e, 0));
}

void teste_removerMorador(){
    face f = getFaceQuadra(qTeste, 0);
    endereco e = getEnderecoFace(f, 0);

    adicionarMoradorEndereco("111", e);
    adicionarMoradorEndereco("222", e);

    removerMoradorEndereco("111", e);

    TEST_ASSERT_EQUAL_INT(1, getQuantidadeMoradoresEndereco(e));
}

void teste_coordenadasEndereco(){
    double x, y;

    getCoordenadasEndereco(qTeste, 'N', 10, &x, &y);

    TEST_ASSERT_EQUAL_DOUBLE(20.0, x); 
    TEST_ASSERT_EQUAL_DOUBLE(70.0, y); 
}

void teste_tipoQuadra_set_get(){
    setEspessuraTipoQuadra(tqTeste, "2px");
    setCorBTipoQuadra(tqTeste, "black");
    setCorPTipoQuadra(tqTeste, "red");

    TEST_ASSERT_EQUAL_STRING("2px", getEspessuraTipoQuadra(tqTeste));
    TEST_ASSERT_EQUAL_STRING("black", getCorBTipoQuadra(tqTeste));
    TEST_ASSERT_EQUAL_STRING("red", getCorPTipoQuadra(tqTeste));
}

void teste_tamanhoQuadra(){
    TEST_ASSERT_TRUE(getTamanhoQuadra() > 0);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_criarQuadra);
    RUN_TEST(teste_gettersQuadra);
    RUN_TEST(teste_facesInicialmenteVazias);
    RUN_TEST(teste_adicionarMorador);
    RUN_TEST(teste_removerMorador);
    RUN_TEST(teste_coordenadasEndereco);
    RUN_TEST(teste_tipoQuadra_set_get);
    RUN_TEST(teste_tamanhoQuadra);

    return UNITY_END();
}