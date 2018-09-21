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
    Funcionario * m_funcionarios[MAX_FUNCIONARIOS];
public:
    Empresa(std::string nome, std::string cnpj);
    ~Empresa();
    void addFuncionario(Funcionario *novoFunc);
    void concederAumento(double aumento);
    int getTotalFuncionarios();
    void operarRh();
    void printFuncionarios();
};

#endif