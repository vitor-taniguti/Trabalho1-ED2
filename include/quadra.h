#ifndef QUADRA_H    
#define QUADRA_H

typedef void* endereco;
typedef void* face;
typedef void* quadra;
typedef void* tipoQuadra;

/*
Módulo responsável na manipulação do objeto quadra, tendo as funções get e set.
Uma quadra é um retângulo, então, possui 4 lados: norte, sul, leste e oeste. 
Cada lado, possui endereços, onde uma ou mais pessoas podem ou não morar lá.
O identificador único da quadra é uma string chamado "cep".
*/

/// @brief Cria uma quadra
/// @param cep Identificador único da quadra
/// @param x Coordenada X da âncora da quadra
/// @param y Coordenada Y da âncora da quadra
/// @param w Largura da quadra
/// @param h Altura da quadra
/// @return A quadra criada com os atributos especificados
quadra criarQuadra(char* cep, double x, double y, double w, double h);

/// @brief Converte a face (char) para um inteiro (0-N, 1-S, 2-L, 3-O)
/// @param face A face que será convertida
int converterFace(char f);

/// @brief Pega o tamanho da memória alocada para a struct quadra
/// @return O tamanho da memória alocada para a struct quadra
int getTamanhoQuadra();

/// @brief Pega a coordenada X da âncora da quadra
/// @param q Ponteiro para a quadra que a coordenada será pega
/// @return A coordenada X da âncora da quadra
double getXQuadra(quadra q);

/// @brief Pega a coordenada Y da âncora da quadra
/// @param q Ponteiro para a quadra que a coordenada será pega
/// @return A coordenada Y da âncora da quadra
double getYQuadra(quadra q);

/// @brief Pega a largura da quadra
/// @param q Ponteiro para a quadra que a largura será pega
/// @return A largura da quadra
double getWQuadra(quadra q);

/// @brief Pega a altura da quadra
/// @param q Ponteiro para a quadra que a largura será pega
/// @return A altura da quadra
double getHQuadra(quadra q);

/// @brief Pega a face do índice e da quadra especificados
/// @param q Ponteiro para a quadra
/// @param indice Índice da face que será pega
/// @return A face com o índice e quadra especificados
face getFaceQuadra(quadra q, int indice);

/// @brief Pega o endereço do índice e da face espeficados
/// @param f Ponteiro para face
/// @param indice Índice do endereco que será pego
/// @return O endereco com o índice e face especificados
endereco getEnderecoFace(face f, int indice);

/// @brief Pega a quantidade de enderecos na face especificada
/// @param f Ponteiro para face
/// @return Quantidade de enderecos da face 
int getQuantidadeEnderecosFace(face f);

/// @brief Aumenta a quantidade de endereços na face especificada
/// @param f Ponteiro para face
void incrementarQuantidadeEnderecosFace(face f);

/// @brief Pega o CPF do morador do índice e do endereço especificado
/// @param e Ponteiro para o endereco do morador
/// @param indice Índice do cpf que será pego
/// @return O CPF do morador do endereco especificado
char* getCpfEndereco(endereco e, int indice);

/// @brief Pega a quantidade de moradores no endereço especificado
/// @param e Ponteiro para o endereço
/// @return A quantidade d emoradores no endereço especificado
int getQuantidadeMoradoresEndereco(endereco e);

/// @brief Define o número do endereço solicitado
/// @param e Endereço que o número será definido
/// @param numero Número do endereço que será definido
void setNumeroEndereco(endereco e, int numero);

/// @brief Busca o endereço de uma quadra, face e número especificados
/// @param q Quadra do endereço
/// @param face Face do endereço
/// @param numero Numero do endereço
/// @return O endereco especificado, NULL se não encontrar
endereco buscarEndereco(quadra q, char face, int numero);

/// @brief Adiciona o cpf de um morador no endereço especificado
/// @param cpf Cpf do morador novo
/// @param e Ponteiro para o endereço do morador novo
void adicionarMoradorEndereco(char* cpf, endereco e);

/// @brief Remove o cpf do morador do endereço especificado
/// @param cpf Cpf do morador que será removido
/// @param e Ponteiro para o endereço que o morador será removido
void removerMoradorEndereco(char* cpf, endereco e);

/// @brief Pega as coordenadas do endereço especificado, com relação à sua quadra, face e número
/// @param q Ponteiro para a quadra do endereço
/// @param face Face do endereço
/// @param numero Número do endereço
/// @param x Endereço da variável que será guardada a coordenada X
/// @param y Endereço da variável que será guardada a coordenada Y
void getCoordenadasEndereco(quadra q, char face, int numero, double* x, double* y);

/// @brief Libera a quadra
/// @param q Ponteiro para quadra
void liberarQuadra(quadra q);

/// @brief Cria um tipo de quadra
/// @return O tipo de quadra criado
tipoQuadra criarTipoQuadra();

/// @brief Pega a espessura do tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
/// @return A espessura do tipo da quadra
char* getEspessuraTipoQuadra(tipoQuadra tq);

/// @brief Pega a cor de borda do tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
/// @return A cor de bordado tipo da quadra
char* getCorBTipoQuadra(tipoQuadra tq);

/// @brief Pega a cor de preenchimento do tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
/// @return A cor de preenchimento do tipo da quadra 
char* getCorPTipoQuadra(tipoQuadra tq);

/// @brief Define a espessura do tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
/// @param sw A espessura do tipo da quadra
void setEspessuraTipoQuadra(tipoQuadra tq, char* sw);

/// @brief Define a cor de bordaa do tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
/// @param cstrk A cor de borda do tipo da quadra
void setCorBTipoQuadra(tipoQuadra tq, char* cstrk);

/// @brief Define a cor de preenchimento do tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
/// @param cfill A cor de preenchimento do tipo da quadra
void setCorPTipoQuadra(tipoQuadra tq, char* cfill);

/// @brief Libera o tipo da quadra
/// @param tq Ponteiro para o tipo da quadra
void liberarTipoQuadra(tipoQuadra tq);

#endif