#ifndef ESTATISTICA_H
#define ESTATISTICA_H

typedef void* estatistica;

/// @brief Cria um objeto estatística 
/// @return A estatística criada
estatistica criarEstatistica();

/// @brief Acrescenta 1 no valor da opção especificada da estatística
/// @param e Ponteiro para a estatística
/// @param opcaoInformacao Opção da estatística (1 - morHom, 2 - morMul, 3 - semTetoHom, 4 - semTetoMul)
/// @param opcaoModificacao Opção de decremento (0) ou incremento (1)
void modificarEstatistica(estatistica e, int opcaoInformacao, int opcaoModificacao);

/// @brief Pega o valor da opção especificada da estatística
/// @param e Ponteiro para a estatística
/// @param opcao Opção da estatística (1 - morHom, 2 - morMul, 3 - semTetoHom, 4 - semTetoMul)
/// @return O valor da opção especificada
int getInfoEstatistica(estatistica e, int opcao);

#endif