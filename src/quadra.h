#ifndef QUADRA_H    
#define QUADRA_H

/*
Módulo responsável na manipulação do objeto quadra, tendo as funções get e set.
Uma quadra é um retângulo, então, possui 4 lados: norte, sul, leste e oeste. 
Cada lado, possui endereços, onde uma pessoa pode ou não morar lá.
O identificador único da quadra é uma string chamado "cep" 
*/

typedef void* endereco;
typedef void* face;
typedef void* quadra;
typedef void* tipoQuadra;

/// @brief Cria uma quadra
/// @param cep Identificador único da quadra
/// @param x Coordenada X da âncora da quadra
/// @param y Coordenada Y da âncora da quadra
/// @param w Largura da quadra
/// @param h Altura da quadra
/// @return A quadra criada com os atributos especificados
quadra criarQuadra(char* cep, double x, double y, double w, double h);

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

/// @brief Pega o CPF do morador do índice e do endereço especificado
/// @param e Ponteiro para o endereco do morador
/// @param indice Índice do cpf que será pego
/// @return O CPF do morador do endereco especificado
char* getCpfEndereco(endereco e, int indice);

/// @brief Pega a quantidade de moradores no endereço especificado
/// @param e Ponteiro para o endereço
/// @return A quantidade d emoradores no endereço especificado
int getQuantidadeMoradoresEndereco(endereco e);

/// @brief Pega a espessura da borda da quadra
/// @param q Ponteiro para quadra
/// @return A espessua da borda da quadra
char* getEspessuraQuadra(quadra q);

/// @brief Pega a cor de borda da quadra
/// @param q Ponteiro para a quadra
/// @return A cor de borda da quadra
char* getCorBQuadra(quadra q);

/// @brief Pega a cor de preenchimento da quadra
/// @param q Ponteiro para a quadra
/// @return A cor de preenchimento da quadra
char* getCorPQuadra(quadra q);

/// @brief Define a espessura da borda da quadra
/// @param q Ponteiro para quadra
/// @param sw A espessura da borda da quadra
void setEspessuraQuadra(quadra q, char* sw);

/// @brief Define a cor de borda da quadra
/// @param q Ponteiro para a quadra 
/// @param cstrk A cor de borda da borda
void setCorBQuadra(quadra q, char* cstrk);

/// @brief Define a cor de preenchimento da quadra
/// @param q Ponteiro para a quadra
/// @param cfill A cor de preenchimento da quadra 
void setCorPQuadra(quadra q, char* cfill);

/// @brief Libera a memória alocada para a quadra
/// @param q Ponteiro para a quadra
void liberarQuadra(quadra q);

#endif