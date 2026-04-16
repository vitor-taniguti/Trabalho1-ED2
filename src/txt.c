#include "txt.h"

void abrirArquivoTxt(arquivo* saida, char* caminhoTxt){
    *saida = fopen(caminhoTxt, "w");
    if (*saida == NULL){
        printf("Falha na alocação de memória!");
        exit(1);
    }
}

void printarLinhaComandoTxt(arquivo txt, char* linhaComando){
    fprintf(txt, "[*] %s\n", linhaComando);
}

void printarDadosPessoa(arquivo txt, pessoa p){
    fprintf(txt, "Nome completo - %s %s\n", getNomePessoa(p), getSobrenomePessoa(p));
    fprintf(txt, "CPF - %s\n", getCpfPessoa(p));
    fprintf(txt, "Sexo - %c\n", getSexoPessoa(p));
    fprintf(txt, "Data de nascimento - %s\n", getNascimentoPessoa(p));

    if (getMoradorPessoa(p) == 0) fprintf(txt, "Esse habitante não é morador\n\n");
}

void printarEnderecoPessoa(arquivo txt, pessoa p){
    fprintf(txt, "Cep - %s\n", getCepPessoa(p));
    fprintf(txt, "Face - %c\n", getFacePessoa(p));
    fprintf(txt, "Número - %d\n", getNumeroPessoa(p));
    fprintf(txt, "Complemento - %s\n\n", getComplementoPessoa(p));
}

void printarCenso(arquivo txt, int nHab, int nMor, double morPhab, int nHom, int nMul, double pHabHom, double pHabMul, double pMorHom, double pMorMul, int nST, double pSTHom, double pSTMul){
    fprintf(txt, "Censo de Bitnópolis:\n\n");
    fprintf(txt, "Número de habitantes - %d\n", nHab);
    fprintf(txt, "Número de moradores - %d\n", nMor);
    fprintf(txt, "Razão morador por habitante - %.2lf\n", morPhab);
    fprintf(txt, "Número de homens - %d\n", nHom);
    fprintf(txt, "Número de mulheres - %d\n", nMul);
    fprintf(txt, "Porcentagem de habitantes homens - %.2lf %%\n", pHabHom);
    fprintf(txt, "Porcentagem de habitantes mulheres - %.2lf %%\n", pHabMul);
    fprintf(txt, "Porcentagem de moradores homens - %.2lf %%\n", pMorHom);
    fprintf(txt, "Porcentagem de moradoras mulheres - %.2lf %%\n", pMorMul);
    fprintf(txt, "Número de sem-tetos - %d\n", nST);
    fprintf(txt, "Porcentagem de homens sem-teto - %.2lf %%\n", pSTHom);
    fprintf(txt, "Porcentagem de mulheres sem-teto - %.2lf %%\n\n", pSTMul);
}
