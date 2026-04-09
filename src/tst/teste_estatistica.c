#include "estatistica.h"
#include "unity.h"

estatistica e;

void setUp(void) {
    e = criarEstatistica();
}

void tearDown(void) {
    liberarEstatistica(e);
}

void teste_criarEstatistica(){
    TEST_ASSERT_NOT_NULL(e);

    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 1));
    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 2));
    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 3));
    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 4));
}

void teste_modificarEstatistica(){
    modificarEstatistica(e, 1, 5); 

    TEST_ASSERT_EQUAL_INT(5, getInfoEstatistica(e, 1));

    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 2)); 
    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 3));

    modificarEstatistica(e, 4, 1);
    TEST_ASSERT_EQUAL_INT(1, getInfoEstatistica(e, 4));

    modificarEstatistica(e, 4, -1);
    modificarEstatistica(e, 2, 1);

    TEST_ASSERT_EQUAL_INT(0, getInfoEstatistica(e, 4)); 
    TEST_ASSERT_EQUAL_INT(1, getInfoEstatistica(e, 2)); 
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_criarEstatistica);
    RUN_TEST(teste_modificarEstatistica);

    return UNITY_END();
}