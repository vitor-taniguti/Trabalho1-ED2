#include "estatistica.h"
#include "geo.h"
#include "hashfile.h"
#include "pessoa.h"
#include "pm.h"
#include "qry.h"
#include "quadra.h"
#include "svg.h"
#include "trataArquivo.h"
#include "txt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define PATH_LEN 512
#define FILE_NAME_LEN 256

typedef FILE* arquivo;

int main(int argc, char *argv[]) {
    char dirEntrada[PATH_LEN] = ".";
    char dirSaida[PATH_LEN] = ".";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoPm[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    int hasGeo = 0, hasSaida = 0, hasQry = 0, hasPm = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            trataCaminho(dirEntrada, PATH_LEN, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            trataCaminho(dirSaida, PATH_LEN, argv[++i]);
            hasSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoQry, argv[++i]);
            hasQry = 1;
        } else if (strcmp(argv[i], "-pm") == 0 && i + 1 < argc) {
            strcpy(nomeArquivoPm, argv[++i]);
            hasPm = 1;
        } else {
            fprintf(stderr, "Parâmetro desconhecido ou inválido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasGeo || !hasSaida) {
        fprintf(stderr, "Erro: parâmetros obrigatórios -f (geo) e -o (saida) não fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[PATH_LEN + FILE_NAME_LEN];
    snprintf(fullPathGeo, sizeof(fullPathGeo), "%s/%s", dirEntrada, nomeArquivoGeo);

    char fullPathPm[PATH_LEN + FILE_NAME_LEN];
    if (hasPm) {
        snprintf(fullPathPm, sizeof(fullPathPm), "%s/%s", dirEntrada, nomeArquivoPm);
    }   

    char fullPathQry[PATH_LEN + FILE_NAME_LEN];
    if (hasQry) {
        snprintf(fullPathQry, sizeof(fullPathQry), "%s/%s", dirEntrada, nomeArquivoQry);
    }

    char baseNomeGeo[FILE_NAME_LEN];
    char baseNomeCombinado[FILE_NAME_LEN];
    
    combinacaoNomeArquivo(nomeArquivoGeo, NULL, baseNomeGeo, sizeof(baseNomeGeo));

    char arquivoSaidaSvgGeo[PATH_LEN + FILE_NAME_LEN];
    snprintf(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), "%s/%s.svg", dirSaida, baseNomeGeo);

    char arquivoSaidaSvgQry[PATH_LEN + FILE_NAME_LEN];
    char arquivoSaidaTxt[PATH_LEN + FILE_NAME_LEN];

    if (hasQry) {
        combinacaoNomeArquivo(nomeArquivoGeo, nomeArquivoQry, baseNomeCombinado, sizeof(baseNomeCombinado));
        snprintf(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry), "%s/%s.svg", dirSaida, baseNomeCombinado);
        snprintf(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), "%s/%s.txt", dirSaida, baseNomeCombinado);
    }

    arquivo geo = NULL;
    arquivo pm = NULL;
    arquivo qry = NULL;
    arquivo txt = NULL;
    arquivo svgGeo = NULL;
    arquivo svgQry = NULL;

    char pathHabitantes[PATH_LEN + FILE_NAME_LEN];
    char pathQuadras[PATH_LEN + FILE_NAME_LEN];
    char* prefixoNome = hasQry ? baseNomeCombinado : baseNomeGeo;

    snprintf(pathHabitantes, sizeof(pathHabitantes), "%s/%s-habitantes", dirSaida, prefixoNome);
    snprintf(pathQuadras, sizeof(pathQuadras), "%s/%s-quadras", dirSaida, prefixoNome);

    hash habitantes = criarHash(pathHabitantes);
    hash quadras = criarHash(pathQuadras);
    tipoQuadra tq = criarTipoQuadra();
    estatistica e = criarEstatistica();

    abrirArquivoGeo(&geo, fullPathGeo);
    abrirArquivoSvg(&svgGeo, arquivoSaidaSvgGeo);
    inicializarSVG(svgGeo);
    lerArquivoGeo(geo, quadras, tq, svgGeo);
    fecharSVG(svgGeo);

    if (hasPm){
        abrirArquivoPm(&pm, fullPathPm);
        lerArquivoPm(pm, habitantes, quadras, e);
    }

    if (hasQry) {
        abrirArquivoQry(&qry, fullPathQry);
        abrirArquivoTxt(&txt, arquivoSaidaTxt);
        abrirArquivoSvg(&svgQry, arquivoSaidaSvgQry);
        inicializarSVG(svgQry);
        lerArquivoQry(qry, txt, svgQry, habitantes, quadras, tq, e);
        fecharSVG(svgQry);
    }

    imprimirDumpHash(habitantes);
    imprimirDumpHash(quadras);

    if (geo) fclose(geo);
    if (pm) fclose(pm);
    if (qry) fclose(qry);
    if (txt) fclose(txt);
    if (svgGeo) fclose(svgGeo);
    if (svgQry) fclose(svgQry);

    liberarHash(habitantes);
    liberarHash(quadras);
    liberarTipoQuadra(tq);
    liberarEstatistica(e);

    return 0;
}