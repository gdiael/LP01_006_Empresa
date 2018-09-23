#ifndef EMPRESA_H
#define EMPRESA_H
#define MAX_FUNCIONARIOS 30
#define RH_KEYS 6

#include "funcionario.h"

class Empresa
{
private:
  std::string m_nome;
  std::string m_cnpj;
  int m_totalFuncionarios;
  Funcionario *m_funcionarios[MAX_FUNCIONARIOS];
  // guarda as opções de linha de comando disponíveis para o operador de Rh
  static std::string m_rhKeyList[RH_KEYS];

public:
  // construtor parametrizado
  Empresa(std::string nome, std::string cnpj);
  // construtor padrão
  Empresa();
  // destrutor
  ~Empresa();
  // retorna m_totalFuncionarios
  int getTotalFuncionarios();
  // retorna m_nome
  std::string getNome();
  // retorna m_cnpj (o texto é formatado antes de ser retorna)
  std::string getCnpj();
  // verifica se o texto passado por cnpj atende todos os requisitos necessários
  // caso sim, retorna true e atribui o valor para m_cnpj
  // caso não, retoran false e não atribui o valor
  bool trySetCnpj(std::string cnpj);
  // tenta adicionar um novo funcionário na empresa, caso já exista um funcionário de mesmo nome
  // será mostrada uma mensagem de erro e o funcionário não é adicionado
  bool addFuncionario(Funcionario *novoFunc);
  // remove o funcionário cujo nome seja igual ao valor passado por funcNome
  // caso não existam funcionários na empresa ou o funcionário solicitado não faça parte da
  // empresa, uma mensagem de erro será mostrada
  bool delFuncionario(std::string funcNome);
  // aumenta o valor do salário de todos os funcionários
  // o proprio é encarregado das entradas do usuário
  void concederAumento();
  // retorna a média somando todos os salarios dos funcionários e dividindo pelo número de funcionários
  // casa não existam funcionários na empresa, uma mensagem de erro será mostrada
  double getMediaSalarial();
  // método responsável por fazer as operações com funcionários da empresa
  // todas as opções disponíveis estão salvos no membro estático m_rhKeyList que é uma array;
  void operarRh();
  // sobrecarga do operador de inserção
  // converte os dados da Empresa em uma stream de texto para o objeto std::cout
  friend std::ostream &operator<<(std::ostream &os, Empresa &emp);
  // sobrecarga do operador de extração
  // convert o stream de texto gerado pela objeto std::cin nos dados da empresa
  friend std::istream &operator>>(std::istream &is, Empresa &emp);
};

#endif