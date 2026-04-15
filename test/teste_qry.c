#include "qry.h"
#include "geo.h"
#include "pessoa.h"
#include "quadra.h"
#include "hashfile.h"
#include "estatistica.h"
#include "svg.h"
#include "txt.h"
#include "unity.h"

#include <stdio.h>
#include <stdlib.h>

hash habitantesTeste;
hash quadrasTeste;
estatistica estTeste;

arquivo txtTeste;
arquivo svgTeste;

void setUp(void){
    habitantesTeste = criarHash("habitantes_test");
    quadrasTeste = criarHash("quadras_test");
    estTeste = criarEstatistica();

    txtTeste = fopen("teste.txt", "w");
    svgTeste = fopen("teste.svg", "w");

    inicializarSVG(svgTeste);

    tipoQuadra tq = criarTipoQuadra();
    quadra q = criarQuadra("12345-000", 10, 10, 100, 100);
    inserirHash(quadrasTeste, q, "12345-000");

    pessoa p = criarPessoa("111", "Joao", "Silva", 'M', "2000-01-01");
    inserirHash(habitantesTeste, p, "111");
}

void tearDown(void){
    fclose(txtTeste);
    fclose(svgTeste);

    remove("teste.txt");
    remove("teste.svg");

    liberarHash(habitantesTeste);
    liberarHash(quadrasTeste);
    liberarEstatistica(estTeste);
}

void teste_abrirArquivoQry(){
    arquivo f;

    FILE* temp = fopen("teste.qry", "w");
    fprintf(temp, "censo\n");
    fclose(temp);

    abrirArquivoQry(&f, "teste.qry");

    TEST_ASSERT_NOT_NULL(f);

    fclose(f);
    remove("teste.qry");
}

void teste_nasc(){
    nasc("222", "Maria", "Oliveira", 'F', "1999-01-01", habitantesTeste, estTeste);

    pessoa p = buscarHash(habitantesTeste, "222");

    TEST_ASSERT_NOT_NULL(p);

    free(p);
}

void teste_h(){
    h("111", habitantesTeste, txtTeste);

    TEST_PASS();
}


void teste_mud(){
    mud("111", "12345-000", 'N', 10, "Apto1", habitantesTeste, quadrasTeste, estTeste, svgTeste);

    pessoa p = buscarHash(habitantesTeste, "111");

    TEST_ASSERT_EQUAL_CHAR('N', getFacePessoa(p));

    free(p);
}

void teste_dspj(){
    mud("111", "12345-000", 'N', 10, "Apto1", habitantesTeste, quadrasTeste, estTeste, svgTeste);

    dspj("111", habitantesTeste, quadrasTeste, estTeste, txtTeste, svgTeste);

    pessoa p = buscarHash(habitantesTeste, "111");

    TEST_ASSERT_EQUAL_INT(0, getMoradorPessoa(p));

    free(p);
}

void teste_rip(){
    rip("111", habitantesTeste, quadrasTeste, estTeste, txtTeste, svgTeste);

    pessoa p = buscarHash(habitantesTeste, "111");

    TEST_ASSERT_NULL(p);
}

void teste_rq(){
    rq("12345-000", habitantesTeste, quadrasTeste, txtTeste, svgTeste);

    quadra q = buscarHash(quadrasTeste, "12345-000");

    TEST_ASSERT_NULL(q);
}

void teste_pq(){
    pq("12345-000", habitantesTeste, quadrasTeste, svgTeste);

    TEST_PASS();
}

void teste_censo(){
    censo(estTeste, txtTeste);

    TEST_PASS();
}

void teste_lerArquivoQry(){
    FILE* temp = fopen("teste.qry", "w");

    fprintf(temp, "nasc 333 Ana Souza F 2001-01-01\n");
    fprintf(temp, "mud 333 12345-000 N 5 Ap\n");
    fprintf(temp, "h? 333\n");
    fprintf(temp, "censo\n");

    fclose(temp);

    arquivo f;
    abrirArquivoQry(&f, "teste.qry");

    lerArquivoQry(f, txtTeste, svgTeste, habitantesTeste, quadrasTeste, estTeste);

    pessoa p = buscarHash(habitantesTeste, "333");

    TEST_ASSERT_NOT_NULL(p);

    fclose(f);
    remove("teste.qry");

    free(p);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_abrirArquivoQry);
    RUN_TEST(teste_nasc);
    RUN_TEST(teste_h);
    RUN_TEST(teste_mud);
    RUN_TEST(teste_dspj);
    RUN_TEST(teste_rip);
    RUN_TEST(teste_rq);
    RUN_TEST(teste_pq);
    RUN_TEST(teste_censo);
    RUN_TEST(teste_lerArquivoQry);

    return UNITY_END();
}