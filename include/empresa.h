#ifndef EMPRESA_H
#define EMPRESA_H
#define MAX_FUNCIONARIOS 30
#define RH_KEYS 5

#include "empresa.h"
#include "funcionario.h"

class Empresa
{
  private:
    std::string m_nome;
    std::string m_cnpj;
    int m_totalFuncionarios;
    Funcionario *m_funcionarios[MAX_FUNCIONARIOS];
    static std::string m_rhKeyList[RH_KEYS];

  public:
    Empresa(std::string nome, std::string cnpj);
    Empresa();
    ~Empresa();
    int getTotalFuncionarios();
    std::string getNome();
    std::string getCnpj();
    bool trySetCnpj(std::string cnpj);
    bool addFuncionario(Funcionario *novoFunc);
    bool delFuncionario(std::string funcNome);
    void concederAumento(double fatorDeAumento);
    double getMediaSalarial();
    void operarRh();
    friend std::ostream &operator<<(std::ostream &os, Empresa &emp);
    friend std::istream &operator>>(std::istream &is, Empresa &emp);
};

#endif