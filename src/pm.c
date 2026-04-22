#include "pm.h"
#include "pessoa.h"
#include <stdlib.h>
#include <string.h>

void abrirArquivoPm(arquivo *pm, char *caminhoPm){
    *pm = fopen(caminhoPm, "r");
    if(*pm == NULL){
        printf("Erro na abertura do arquivo pm!\n");
        exit(1);
    }
}

static void processarLinha(char* linha, char* comando, hash habitantes, hash quadras, estatistica e){
    char cpf[15] = {0}, nome[50] = {0}, sobrenome[50] = {0}, sexo = ' ', nascimento[11] = {0};
    char cep[10] = {0}, complemento[10] = {0}, lado = ' ', tipo[2] = {0};
    int numero = 0;
    
    if (strcmp(comando, "p") == 0){
        sscanf(linha, "%1s %14s %s %s %c %10s", tipo, cpf, nome, sobrenome, &sexo, nascimento);

        pessoa p = criarPessoa(cpf, nome, sobrenome, sexo, nascimento);
        inserirHash(habitantes, p, cpf);

        modificarEstatistica(e, 3, 1);

        free(p);
    } else if (strcmp(comando, "m") == 0){
        sscanf(linha, "%1s %14s %9s %c %d %9s", tipo, cpf, cep, &lado, &numero, complemento);

        quadra q = buscarHash(quadras, cep);

        if (q == NULL) printf("Quadra não encontrada!\n");

        endereco end = buscarEndereco(q, lado, numero);

        if (end == NULL){
            face f = getFaceQuadra(q, converterFace(lado));
            int qtdEndFaces = getQuantidadeEnderecosFace(f);
            end = getEnderecoFace(f, qtdEndFaces);
            
            setNumeroEndereco(end, numero);
            incrementarQuantidadeEnderecosFace(f);
        }

        adicionarMoradorEndereco(cpf, end);

        atualizarHash(quadras, q, cep);

        free(q);

        pessoa p = buscarHash(habitantes, cpf);

        if (p != NULL){
            setCepPessoa(p, cep);
            setFacePessoa(p, lado);
            setNumeroPessoa(p, numero);
            setComplementoPessoa(p, complemento);
            setMoradorPessoa(p, 1);

            atualizarHash(habitantes, p, cpf);

            modificarEstatistica(e, getSexoPessoa(p) == 'M' ? 1 : 2, 1);
            modificarEstatistica(e, getSexoPessoa(p) == 'M' ? 3 : 4, -1);

            free(p); 
        } else printf("Habitante com CPF %s não encontrado.\n", cpf);
    }
}

void lerArquivoPm(arquivo pm, hash habitantes, hash quadras, estatistica e){
    if (pm == NULL){
        printf("O arquivo pm não foi aberto!\n");
        exit(1);
    }

    char linha[256], comando[2];

    while (fgets(linha, sizeof(linha), pm)){
        int i = 0;

        while (linha[i] != ' ' && linha[i] != '\n' && linha[i] != '\0'){
            comando[i] = linha[i];
            i++;
        }

        comando[i] = '\0';

        processarLinha(linha, comando, habitantes, quadras, e);
    }
}