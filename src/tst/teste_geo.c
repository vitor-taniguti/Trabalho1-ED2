#include "geo.h"
#include "unity.h"
#include <stdlib.h>

hash quadrasTeste;
tipoQuadra tqTeste;
arquivo svgTeste;

void setUp(void) {
    quadrasTeste = criarHash(100); 
}

void tearDown(void) {
    remove("teste_saida.svg");
    remove("temporario.geo");
}

void teste_abrirArquivoGeo(){
    arquivo meuArquivo;

    arquivo temp = fopen("temporario.geo", "w");
    fprintf(temp, "arquivo de teste\n");
    fclose(temp);

    abrirArquivoGeo(&meuArquivo, "temporario.geo");

    TEST_ASSERT_NOT_NULL(meuArquivo);

    fclose(meuArquivo);
}

void teste_lerArquivoGeo(){
    arquivo leituraGeo;

    arquivo temp = fopen("temporario.geo", "w");
    fprintf(temp, "cq 1.0px gold MediumAquamarine\n");
    fprintf(temp, "q 12345-000 10.0 20.0 100.0 100.0\n"); 
    fclose(temp);

    abrirArquivoGeo(&leituraGeo, "temporario.geo");

    lerArquivoGeo(leituraGeo, quadrasTeste, tqTeste, svgTeste);
    fclose(leituraGeo);

    quadra qEncontrada = buscarHash(quadrasTeste, "12345-000");
    
    TEST_ASSERT_NOT_NULL(qEncontrada);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_abrirArquivoGeo);
    RUN_TEST(teste_lerArquivoGeo);

    return UNITY_END();
}