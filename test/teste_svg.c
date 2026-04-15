#include "svg.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arquivo svgTeste;

void setUp(void){
    abrirArquivoSvg(&svgTeste, "teste.svg");
}

void tearDown(void){
    fclose(svgTeste);
    remove("teste.svg");
}

void teste_abrirArquivoSvg(){
    arquivo f;
    abrirArquivoSvg(&f, "temp.svg");
    TEST_ASSERT_NOT_NULL(f);
    fclose(f);
    remove("temp.svg");
}

void teste_inicializarSVG(){
    inicializarSVG(svgTeste);
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[200];
    fgets(buffer, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<svg"));
    fclose(f);
}

void teste_inserirRetanguloSVG(){
    inicializarSVG(svgTeste);
    inserirRetanguloSVG(svgTeste, 10, 20, 30, 40, "red", "blue");
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<rect"));
    fclose(f);
}

void teste_inserirCirculoSVG(){
    inicializarSVG(svgTeste);
    inserirCirculoSVG(svgTeste, 10, 20, 5, "green", "black");
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<circle"));
    fclose(f);
}

void teste_inserirTextoSVG(){
    inicializarSVG(svgTeste);
    inserirTextoSVG(svgTeste, "teste", 10, 20, 'm');
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<text"));
    fclose(f);
}

void teste_inserirXSVG(){
    inicializarSVG(svgTeste);
    inserirXSVG(svgTeste, 10, 20, "red");
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<line"));
    fclose(f);
}

void teste_inserirCruzSVG(){
    inicializarSVG(svgTeste);
    inserirCruzSVG(svgTeste, 10, 20, "blue");
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "<line"));
    fclose(f);
}

void teste_fecharSVG(){
    inicializarSVG(svgTeste);
    fecharSVG(svgTeste);
    fflush(svgTeste);

    FILE* f = fopen("teste.svg", "r");
    char buffer[500];
    fread(buffer, 1, sizeof(buffer), f);

    TEST_ASSERT_NOT_NULL(strstr(buffer, "</svg>"));
    fclose(f);
}

int main(){
    UNITY_BEGIN();

    RUN_TEST(teste_abrirArquivoSvg);
    RUN_TEST(teste_inicializarSVG);
    RUN_TEST(teste_inserirRetanguloSVG);
    RUN_TEST(teste_inserirCirculoSVG);
    RUN_TEST(teste_inserirTextoSVG);
    RUN_TEST(teste_inserirXSVG);
    RUN_TEST(teste_inserirCruzSVG);
    RUN_TEST(teste_fecharSVG);

    return UNITY_END();
}