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
    Funcionario(std::string nome, double salario);
    Funcionario();
    ~Funcionario();
    static std::string askForName(std::istream &is, std::string mensagem);
    std::string getNome();
    double getSalario();
    void setSalario(double valor);
    bool trySetSalario(std::string valor);
    bool operator==(Funcionario &outro);
    friend std::istream &operator>>(std::istream &is, Funcionario &func);
    friend std::ostream &operator<<(std::ostream &os, Funcionario &func);
};

std::string str_toupper(std::string s);

#endif