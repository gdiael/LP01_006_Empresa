#ifndef EMPRESA_H
#define EMPRESA_H
#define MAX_FUNCIONARIOS 30

#include "empresa.h"
#include "funcionario.h"

class Empresa
{
  private:
    std::string m_nome;
    std::string m_cnpj;
    int m_totalFuncionarios;
    Funcionario *m_funcionarios[MAX_FUNCIONARIOS];

  public:
    Empresa(std::string nome, std::string cnpj);
    Empresa();
    ~Empresa();
    int getTotalFuncionarios();
    std::string getNome();
    std::string getCnpj();
    bool trySetCnpj(std::string cnpj);
    void addFuncionario(Funcionario *novoFunc);
    void concederAumento(double aumento);
    void operarRh();
    friend std::ostream &operator<<(std::ostream &os, Empresa &emp);
    friend std::istream &operator>>(std::istream &is, Empresa &emp);
};

#endif