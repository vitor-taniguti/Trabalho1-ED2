#include "estatistica.h"

typedef struct{
    int morHom;
    int morMul;
    int semTetoHom;
    int semTetoMul;
} Estatistica;

estatistica criarEstatistica(){
    Estatistica* est = malloc(sizeof(Estatistica));

    est->morHom = 0;
    est->morMul = 0;
    est->semTetoHom = 0;
    est->semTetoMul = 0;

    return (Estatistica*) est;
}

void modificarEstatistica(estatistica e, int opcaoInformacao, int opcaoModificacao){
    Estatistica* est = (Estatistica*) e;

    int modificacao = opcaoModificacao ? -1 : 1;

    switch (opcaoInformacao){
        case 1:
            est->morHom += modificacao;
            break;
        case 2:
            est->morMul += modificacao;
            break;
        case 3:
            est->semTetoHom += modificacao;
            break;
        case 4:
            est->semTetoMul += modificacao;
            break;
        default:
            printf("Opção inválida ao modificar estatística!\n");
            break;
    }
}

int getInfoEstatistica(estatistica e, int opcao){
    Estatistica* est = (Estatistica*) e;

    switch (opcao){
        case 1: return est->morHom;
        case 2: return est->morMul;
        case 3: return est->semTetoHom;
        case 4: return est->semTetoMul;
        default:
            printf("Opção inválida ao acrescentar estatística!\n");
            break;
    }

    return -1;
}
