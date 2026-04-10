#ifndef ESTATISTICA_H
#define ESTATISTICA_H

/*
Módulo responsável pelo gerenciamento do objeto Estatistica, que guarda informações da população de Bitnópolis.
Esse módulo apresenta funções responsáveis por modificar e pegar as informações da struct Estatistica.
As informações guardadas são os números de: moradores homens, moradores mulheres, homens sem-teto e mulheres sem-teto.
Apenas com essas informações, podemos deduzir muitas outras estatísticas da cidade.
*/

typedef void* estatistica;

/// @brief Cria um objeto estatística 
/// @return A estatística criada
estatistica criarEstatistica();

/// @brief Acrescenta 1 no valor da opção especificada da estatística
/// @param e Ponteiro para a estatística
/// @param opcaoInformacao Opção da estatística (1 - morHom, 2 - morMul, 3 - semTetoHom, 4 - semTetoMul)
/// @param opcaoModificacao Valor da modificação da estatística
void modificarEstatistica(estatistica e, int opcaoInformacao, int valorModificacao);

/// @brief Pega o valor da opção especificada da estatística
/// @param e Ponteiro para a estatística
/// @param opcao Opção da estatística (1 - morHom, 2 - morMul, 3 - semTetoHom, 4 - semTetoMul)
/// @return O valor da opção especificada
int getInfoEstatistica(estatistica e, int opcao);

/// @brief Libera a memória alocada para a struct estatística
/// @param e Ponteiro para a estatística 
void liberarEstatistica(estatistica e);

#endif