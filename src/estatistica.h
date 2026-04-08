#ifndef ESTATISTICA_H
#define ESTATISTICA_H

typedef void* estatistica;

/// @brief Cria um objeto estatística 
/// @return A estatística criada
estatistica criarEstatistica();

/// @brief Acrescenta 1 no valor da opção especificada da estatística
/// @param e Ponteiro para a estatística
/// @param opcao Opção da estatística (1 - morHom, 2 - morMul, 3 - semTetoHom, 4 - semTetoMul)
void acrescentarEstatistica(estatistica e, int opcao);

/// @brief Pega o valor da opção especificada da estatística
/// @param e Ponteiro para a estatística
/// @param opcao Opção da estatística (1 - morHom, 2 - morMul, 3 - semTetoHom, 4 - semTetoMul)
/// @return O valor da opção especificada
int getInfoEstatitisca(estatistica e, int opcao);

#endif