#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#define MIN_SALARIO 954.0

#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>

class Funcionario
{
private:
  std::string m_nome;
  double m_salario;

public:
  // construtor parametrizado
  Funcionario(std::string nome, double salario);
  // contrutor padrão
  Funcionario();
  // destrutor
  ~Funcionario();
  // método para solicitar ao usuário um novo nome de funcionário
  // será mostrado o conteúdo da parametro mensagem na linha de comando
  static std::string askForName(std::istream &is, std::string mensagem);
  // retorna m_nome
  std::string getNome();
  // retorna m_salario
  double getSalario();
  // atualiza o valor de m_salario
  void giveAumentoSalario(double fatorDeAumento);
  // verifica se o valor passado pelo atributo "valor" pode ser
  // convertido em double e atende os requisitos necessários
  // caso sim, retorna true e atualiza o valor de m_salario
  // caso não, retorna false e não atualiza o valor
  bool trySetSalario(std::string valor);
  // operador de comparação entre dois Funcionarios
  bool operator==(Funcionario &outro);
  // operador de extração de um funcionário novo
  friend std::istream &operator>>(std::istream &is, Funcionario &func);
  // operador de conversão da Classe funcionário em um stream de texto
  friend std::ostream &operator<<(std::ostream &os, Funcionario &func);
};

// função auxiliar para conversão do texto passado por "s" em CAIXA ALTA
std::string str_toupper(std::string s);

#endif