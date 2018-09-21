#include "funcionario.h"
#include <iomanip>

Funcionario::Funcionario(std::string nome, double salario) : m_nome(nome), m_salario(salario) {}

Funcionario::Funcionario() : m_nome(""), m_salario(0.0) {}

Funcionario::~Funcionario() {}

std::string Funcionario::getNome()
{
    return m_nome;
}

double Funcionario::getSalario()
{
    return m_salario;
}

void Funcionario::setSalario(double valor)
{
    m_salario = valor;
}

bool Funcionario::operator==(Funcionario &outro)
{
    return (m_nome == outro.getNome());
}

std::istream &operator>>(std::istream &i, Funcionario &func)
{
    do
    {
        std::cout << "\nDigite o nome do novo Funcionário: ";
        i >> func.m_nome;
        if (func.m_nome == "" || func.m_nome == " ")
        {
            std::cout << "Estes valores não são válidos!";
        };
    } while (func.m_nome == "" || func.m_nome == " ");

    do
    {
        std::cout << "Digite o salário de [" << func.m_nome << "] : ";
        std::string valor;
        i >> valor;
        bool isGoodStr = true;
        try
        {
            func.m_salario = std::stod(valor);
        }
        catch (std::exception &ia)
        {
            std::cout << "Estes valores não são válidos!\n";
            isGoodStr = false;
        };
        if (isGoodStr)
        {
            if (func.m_salario < MIN_SALARIO)
            {
                std::cout << "O salário não pode ser inferior ao salário mínimo (R$ " << MIN_SALARIO << ")!!!\n";
            };
        }

    } while (func.m_salario < MIN_SALARIO);

    return i;
}

std::ostream &operator<<(std::ostream &os, Funcionario &func)
{
    // aqui serão usados manipuladores para formatar a saída
    // o nome do funcionário será ajustado a esquerda, e terá um espaçamento de 15
    // caracteres antes do salário
    os << std::left << std::setw(15) << func.m_nome;
    // o salário será formatado com duas casas decimais
    os << " [R$ " << std::setprecision(2) << std::fixed;
    // será ajustado a direito com espaçamento de 8 caracteres
    os << std::right << std::setw(8) << func.m_salario << "]" << std::endl;
    return os;
}