#ifndef PESSOA_H
#define PESSOA_H

/*
Módulo responsável na manipulação do objeto pessoa, contendo as funções de get e set referentes.
*/

typedef void* pessoa;

/// @brief Cria uma pessoa com os atributos especificados
/// @param cpf Identificador único de pessoa
/// @param nome Nome da pessoa
/// @param sobrenome Sobrenome da pessoa
/// @param sexo Sexo da pessoa
/// @param nascimento Data de nascimento da pessoa
/// @return Pessoa criada com os atributos especificados
pessoa criarPessoa(char* cpf, char* nome, char* sobrenome, char sexo, char* nascimento);

/// @brief Pega o tamanho da memória alocada para a struct pessoa
/// @return O tamanho da memória alocada para a struct pessoa
int getTamanhoPessoa();

/// @brief Pega o CPF da pessoa
/// @param p Ponteiro para a pessoa
/// @return O CPF da pessoa
char* getCpfPessoa(pessoa p);

/// @brief Pega o nome da pessoa 
/// @param p Ponteiro para a pessoa
/// @return O nome da pessoa
char* getNomePessoa(pessoa p);

/// @brief Pega o sobrenome da pessoa
/// @param p Ponteiro para a pessoa
/// @return O sobrenome da pessoa
char* getSobrenomePessoa(pessoa p);

/// @brief Pega o sexo da pessoa
/// @param p Ponteiro para a pessoa
/// @return O sexo da pessoa
char getSexoPessoa(pessoa p);

/// @brief Pega a data de nascimento da pessoa
/// @param p Ponteiro para a pessoa
/// @return A data de nascimento da pessoa
char* getNascimentoPessoa(pessoa p);

/// @brief Pega o CEP da pessoa
/// @param p Ponteiro para pessoa
/// @return O CEP da pessoa
char* getCepPessoa(pessoa p);

/// @brief Pega o a face da quadra que a pessoa mora
/// @param p Ponteiro para pessoa
/// @return A face da quadra que a pessoa mora
char getFacePessoa(pessoa p);

/// @brief Pega o número da residência da pessoa
/// @param p Ponteiro para pessoa
/// @return O número da residência da pessoa
int getNumeroPessoa(pessoa p);

/// @brief Pega o complemento da residência da pessoa
/// @param p Ponteiro para pessoa
/// @return O complemento da residência da pessoa
char* getComplementoPessoa(pessoa p);

/// @brief Pega a situação de moradia da pessoa
/// @param p Ponteiro para a pessoa
/// @return A situação de moradia da pessoa (0 - sem teto, 1 - morador)
int getMoradorPessoa(pessoa p);

/// @brief Define a CEP da pessoa
/// @param p Ponteiro para a pessoa
/// @param cep O CEP novo da pessoa 
void setCepPessoa(pessoa p, char* cep);

/// @brief Define a face da residência da pessoa
/// @param p Ponteiro para a pessoa
/// @param face A face da residência da pessoa
void setFacePessoa(pessoa p, char face);

/// @brief Define o número da residência da pessoa
/// @param p Ponteiro para a pessoa
/// @param numero Número da residência da pessoa
void setNumeroPessoa(pessoa p, int numero);

/// @brief Define o complemento da residência da pessoa
/// @param p Ponteiro para a pessoa
/// @param complemento O complemento da residência da pessoa
void setComplementoPessoa(pessoa p, char* complemento);

/// @brief Define se a pessoa é moradora ou não (0 - sem teto, 1 - morador)
/// @param p Ponteiro para pessoa
/// @param morador Inteiro identificador de morador (0 - sem teto, 1 - morador)
void setMoradorPessoa(pessoa p, int morador);

/// @brief Libera a memória alocada para a pessoa
/// @param p Ponteiro para a pessoa
void liberarPessoa(pessoa p);

#endif