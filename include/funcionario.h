#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H
#define MIN_SALARIO 954.0

#include <string>
#include <iostream>

class Funcionario
{
private:
    std::string m_nome;
    double m_salario;
public:
    Funcionario(std::string nome, double salario);
    Funcionario();
    ~Funcionario();
    std::string getNome();
    double getSalario();
    void setSalario(double valor);
    bool operator == (Funcionario &outro);
    friend std::istream& operator>> (std::istream &is, Funcionario &novo);
    friend std::ostream& operator<< (std::ostream &os, Funcionario &novo);
};

#endif