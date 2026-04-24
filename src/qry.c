#include "qry.h"
#include "pessoa.h"
#include "quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void abrirArquivoQry(arquivo *qry, char *caminhoQry){
    *qry = fopen(caminhoQry, "r");
    if(*qry == NULL){
        printf("Erro na abertura do arquivo qry!\n");
        exit(1);
    }
}

void rq(char* cep, hash habitantes, hash quadras, arquivo txt, arquivo svg){
    quadra q = buscarHash(quadras, cep);

    if (q == NULL){
        printf("Quadra não encontrada para ser removida!\n");
        return;
    }

    fprintf(txt, "Dados dos moradores que viraram sem-teto:\n\n");

    int haMoradores = 0;

    for (int i = 0; i < 4; i++){
        face f = getFaceQuadra(q, i);
        int qtdEnd = getQuantidadeEnderecosFace(f);

        for(int j = 0; j < qtdEnd; j++){
            endereco end = getEnderecoFace(f, j);
            int qtdMor = getQuantidadeMoradoresEndereco(end);

            if (qtdMor != 0) haMoradores = 1;

            for (int k = 0; k < qtdMor; k++){
                char* cpfMorador = getCpfEndereco(end, k);
                pessoa p = buscarHash(habitantes, cpfMorador);

                setMoradorPessoa(p, 0);
                printarDadosPessoa(txt, p);

                atualizarHash(habitantes, p, cpfMorador); 
                free(p);
            }
        }
    }

    if (!haMoradores) fprintf(txt, "Não há moradores para serem despejados dessa quadra!\n\n");

    inserirXSVG(svg, getXQuadra(q), getYQuadra(q), "red");

    removerHash(quadras, cep);

    free(q);
}

void pq(char* cep, hash quadras, arquivo svg){
    int faces[4] = {0, 0, 0, 0}, total = 0;
    char stringFaces[4][5], stringTotal[5];

    quadra q = buscarHash(quadras, cep);

    if (q == NULL){
        printf("Quadra não encontrada para ser obter número de habitantes!\n");
        return;
    }

    for (int i = 0; i < 4; i++){
        face f = getFaceQuadra(q, i);
        int qtdEnd = getQuantidadeEnderecosFace(f);

        for (int j = 0; j < qtdEnd; j++){
            endereco end = getEnderecoFace(f, j);

            if (end == NULL){
                printf("Endereço não encontrado para pegar quantidade de moradores!\n");
                return;
            }

            int qtdMor = getQuantidadeMoradoresEndereco(end);

            faces[i] += qtdMor;
            total += qtdMor;
        }
    }

    for (int i = 0; i < 4; i++){
        snprintf(stringFaces[i], sizeof(stringFaces[i]), "%d", faces[i]);
    }
    snprintf(stringTotal, sizeof(stringTotal), "%d", total);

    double x = getXQuadra(q);
    double y = getYQuadra(q);
    double w = getWQuadra(q);
    double h = getHQuadra(q);

    inserirTextoSVG(svg, stringFaces[0], x+(w/2), y+h-5, 'm');
    inserirTextoSVG(svg, stringFaces[1], x+(w/2), y+15, 'm');
    inserirTextoSVG(svg, stringFaces[2], x+10, y+(h/2), 'f');
    inserirTextoSVG(svg, stringFaces[3], x+w-10, y+(h/2), 'i');
    inserirTextoSVG(svg, stringTotal, x+(w/2), y+(h/2), 'm');

    free(q);
}

void censo(estatistica e, arquivo txt){
    int morHom = getInfoEstatistica(e, 1), morMul = getInfoEstatistica(e, 2);
    int semTetoHom = getInfoEstatistica(e, 3), semTetoMul = getInfoEstatistica(e, 4);

    int nHab = morHom + morMul + semTetoHom + semTetoMul;
    int nMor = morHom + morMul;
    int nHom = morHom + semTetoHom;
    int nMul = morMul + semTetoMul;
    int nST = semTetoHom + semTetoMul;

    if (nHab == 0){
        printf("A cidade de Bitnópolis está vazia! Censo não gerado.\n");
        return;
    }

    double morPhab = (double) nMor / nHab; 
    double pHabHom = ((double) nHom / nHab) * 100.0;
    double pHabMul = ((double) nMul / nHab) * 100.0;
    double pMorHom = (nMor > 0) ? (((double) morHom / nMor) * 100.0) : 0.0;
    double pMorMul = (nMor > 0) ? (((double) morMul / nMor) * 100.0) : 0.0;
    double pSTHom = (nST > 0) ? (((double) semTetoHom / nST) * 100.0) : 0.0;
    double pSTMul = (nST > 0) ? (((double) semTetoMul / nST) * 100.0) : 0.0;
    
    printarCenso(txt, nHab, nMor, morPhab, nHom, nMul, pHabHom, pHabMul, pMorHom, pMorMul, nST, pSTHom, pSTMul);
}

void h(char* cpf, hash habitantes, arquivo txt){
    pessoa p = buscarHash(habitantes, cpf);

    if (p == NULL){
        printf("Habitante não encontrado para buscar dados!\n");
        return;
    }

    fprintf(txt, "Dados do habitante:\n\n");
    printarDadosPessoa(txt, p);

    if (getMoradorPessoa(p) == 1) printarEnderecoPessoa(txt, p);

    free(p);
}

void nasc(char* cpf, char* nome, char* sobrenome, char sexo, char* nascimento, hash habitantes, estatistica e){
    pessoa p = criarPessoa(cpf, nome, sobrenome, sexo, nascimento);

    inserirHash(habitantes, p, cpf);
    
    modificarEstatistica(e, (sexo == 'M' ? 3 : 4), 1);

    free(p);
}

void rip(char* cpf, hash habitantes, hash quadras, estatistica e, arquivo txt, arquivo svg){
    pessoa p = buscarHash(habitantes, cpf);

    if (p == NULL){
        fprintf(txt, "Habitante com CPF %s não encontrado para falecer!\n\n", cpf);
        return;
    }

    fprintf(txt, "Dados do habitante falecido:\n\n");
    printarDadosPessoa(txt, p);

    if (getMoradorPessoa(p) == 1){
        printarEnderecoPessoa(txt, p);

        modificarEstatistica(e, (getSexoPessoa(p) == 'M' ? 1 : 2), -1);

        char* cepAntigo = getCepPessoa(p);
        quadra q = buscarHash(quadras, cepAntigo);
        endereco end = buscarEndereco(q, getFacePessoa(p), getNumeroPessoa(p));

        removerMoradorEndereco(cpf, end);
        atualizarHash(quadras, q, cepAntigo);

        if (getMoradorPessoa(p) == 1){
            double x, y;
            getCoordenadasEndereco(q, getFacePessoa(p), getNumeroPessoa(p), &x, &y);
            inserirCruzSVG(svg, x, y, "red");
        }

        free(q);
    } else modificarEstatistica(e, (getSexoPessoa(p) == 'M' ? 3 : 4), -1);

    removerHash(habitantes, cpf);

    free(p);
}

void mud(char* cpf, char* cep, char lado, int numero, char* complemento, hash habitantes, hash quadras, estatistica e, arquivo svg){
    pessoa p = buscarHash(habitantes, cpf);

    if (p == NULL){
        printf("Pessoa não encontrada para se mudar!\n");
        return;
    }

    quadra qNova = buscarHash(quadras, cep);
    endereco endNovo = buscarEndereco(qNova, lado, numero);

    if (endNovo == NULL){
        printf("Endereço %s/%c/%d/%s não encontrado para mudar pessoa!\n", cep, lado, numero, complemento);

        free(qNova);
        free(p);

        return;
    }

    if (getMoradorPessoa(p) == 1){
        char* cepAntigo = getCepPessoa(p);
        quadra qAntiga = buscarHash(quadras, cepAntigo);
        endereco endAntigo = buscarEndereco(qAntiga, getFacePessoa(p), getNumeroPessoa(p));

        if (endAntigo != NULL){
            removerMoradorEndereco(cpf, endAntigo);
            atualizarHash(quadras, qAntiga, cepAntigo);
        }

        free(qAntiga);
    } else{
        modificarEstatistica(e, (getSexoPessoa(p) == 'M' ? 1 : 2), 1);
        modificarEstatistica(e, (getSexoPessoa(p) == 'M' ? 3 : 4), -1);

        setMoradorPessoa(p, 1);
    }

    adicionarMoradorEndereco(cpf, endNovo);
    atualizarHash(quadras, qNova, cep);

    free(qNova);

    setCepPessoa(p, cep);
    setFacePessoa(p, lado);
    setNumeroPessoa(p, numero);
    setComplementoPessoa(p, complemento);

    atualizarHash(habitantes, p, cpf); 
    free(p);

    double x, y;

    getCoordenadasEndereco(buscarHash(quadras, cep), lado, numero, &x, &y);

    inserirRetanguloSVG(svg, x, y, 5.0, 5.0, "red", "red");
    inserirTextoSVG(svg, cpf, x, y, 'm');
}

void dspj(char* cpf, hash habitantes, hash quadras, estatistica e, arquivo txt, arquivo svg){
    pessoa p = buscarHash(habitantes, cpf);

    if (p == NULL){
        printf("Pessoa não encontrada para despejar!\n");
        return;
    }

    if (getMoradorPessoa(p) == 0){
        fprintf(txt, "Pessoa de CPF %s não é moradora para ser despejada!\n\n", cpf);
        free(p);
        return;
    }

    modificarEstatistica(e, (getSexoPessoa(p) == 'M' ? 1 : 2), -1);
    modificarEstatistica(e, (getSexoPessoa(p) == 'M' ? 3 : 4), 1);

    fprintf(txt, "Dados da pessoa que foi despejada:\n\n");
    printarDadosPessoa(txt, p);
    printarEnderecoPessoa(txt, p);

    char* cepAntigo = getCepPessoa(p);
    quadra q = buscarHash(quadras, cepAntigo);

    double x, y;

    getCoordenadasEndereco(q, getFacePessoa(p), getNumeroPessoa(p), &x, &y);

    endereco end = buscarEndereco(q, getFacePessoa(p), getNumeroPessoa(p));

    removerMoradorEndereco(cpf, end);
    setMoradorPessoa(p, 0);
    
    atualizarHash(quadras, q, cepAntigo);   
    free(q);

    atualizarHash(habitantes, p, cpf);
    free(p);

    inserirCirculoSVG(svg, x, y, 5, "black", "black");
}

static void processarLinha(char* linha, char* comando, hash habitantes, hash quadras, estatistica e, arquivo txt, arquivo svg){
    char cpf[15] = {0}, nome[50] = {0}, sobrenome[50] = {0}, sexo = ' ', nascimento[11] = {0};
    char cep[10] = {0}, complemento[10] = {0}, lado = ' ', tipo[2] = {0};
    int numero = 0;

    printarLinhaComandoTxt(txt, linha);
    
    if (strcmp(comando, "rq") == 0){
        sscanf(linha, "%2s %9s", tipo, cep);
        rq(cep, habitantes, quadras, txt, svg);
    } else if (strcmp(comando, "pq") == 0){
        sscanf(linha, "%2s %9s", tipo, cep);
        pq(cep, quadras, svg);
    } else if (strcmp(comando, "censo") == 0){
        censo(e, txt);
    } else if (strcmp(comando, "h?") == 0){
        sscanf(linha, "%2s %14s", tipo, cpf);
        h(cpf, habitantes, txt);
    } else if (strcmp(comando, "nasc") == 0){
        sscanf(linha, "%4s %14s %49s %49s %c %10s", tipo, cpf, nome, sobrenome, &sexo, nascimento);
        nasc(cpf, nome, sobrenome, sexo, nascimento, habitantes, e);
    } else if (strcmp(comando, "rip") == 0){
        sscanf(linha, "%3s %14s", tipo, cpf);
        rip(cpf, habitantes, quadras, e, txt, svg);
    } else if (strcmp(comando, "mud") == 0){
        sscanf(linha, "%3s %14s %9s %c %d %9s", tipo, cpf, cep, &lado, &numero, complemento);
        mud(cpf, cep, lado, numero, complemento, habitantes, quadras, e, svg);
    } else if (strcmp(comando, "dspj") == 0){
        sscanf(linha, "%4s %14s", tipo, cpf);
        dspj(cpf, habitantes, quadras, e, txt, svg);
    } else printf("Comando do qry inválido!\n");
}

void lerArquivoQry(arquivo qry, arquivo txt, arquivo svg, hash habitantes, hash quadras, tipoQuadra tq, estatistica e){
    if (qry == NULL){
        printf("O arquivo qry não foi aberto!\n");
        exit(1);
    }

    percorrerHash(quadras, svg, inserirRetanguloSVG, tq);

    char linha[256], comando[6];

    while (fgets(linha, sizeof(linha), qry)){
        int i = 0;

        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }

        comando[i] = '\0';

        processarLinha(linha, comando, habitantes, quadras, e, txt, svg);
    }
}