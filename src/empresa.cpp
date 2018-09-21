#include "funcionario.h"
#include "empresa.h"

Empresa::Empresa(std::string nome, std::string cnpj) : m_nome(nome), m_totalFuncionarios(0)
{
    bool cnpjOK = Empresa::trySetCnpj(cnpj);
    if (!cnpjOK)
    {
        m_cnpj = "00000000000000";
    };
}

Empresa::Empresa() : m_nome("Desconhecida"), m_cnpj("00000000000000"), m_totalFuncionarios(0) {}

Empresa::~Empresa() {}

int Empresa::getTotalFuncionarios()
{
    return m_totalFuncionarios;
}

std::string Empresa::getNome()
{
    return m_nome;
}

std::string Empresa::getCnpj()
{
    return m_cnpj;
}

bool Empresa::trySetCnpj(std::string cnpj)
{
    int size = cnpj.size();
    if (size != 14)
    {
        std::cout << "O CNPJ precisa ter 14 caracteres numéricos exatamente!" << std::endl;
        return false;
    };

    std::string numList = "0123456789";
    for (int i = 0; i < size; i++)
    {
        char c = cnpj[i];
        if (numList.find(c) == std::string::npos)
        {
            std::cout << "Dígite apenas números!" << std::endl;
            return false;
        };
    }

    m_cnpj = cnpj;
    return true;
}

void Empresa::addFuncionario(Funcionario *novoFunc)
{
    if (m_totalFuncionarios == MAX_FUNCIONARIOS)
    {
        std::cerr << "A empresa já está lotada!" << std::endl;
    }
    else
    {
        bool canAdd = true;
        for (int i = 0; (canAdd && i < m_totalFuncionarios); i++)
        {
            if (*m_funcionarios[i] == *novoFunc)
            {
                canAdd = false;
            };
        };
        if (canAdd)
        {
            m_funcionarios[m_totalFuncionarios++] = novoFunc;
        }
        else
        {
            std::cerr << "O funcionário já foi adicionado!" << std::endl;
        };
    };
}

void Empresa::concederAumento(double aumento)
{
}

void Empresa::operarRh()
{
}

std::ostream &operator<<(std::ostream &os, Empresa &emp)
{
    os << "\nEmpresa: " << emp.m_nome << " [CNPJ: " << emp.m_cnpj << "]" << std::endl;
    os << "Constituída por " << emp.m_totalFuncionarios << " funcionários, à saber:" << std::endl;
    for (int i = 0; i < emp.m_totalFuncionarios; i++)
    {
        os << "   " << *emp.m_funcionarios[i];
    };
    return os;
}

std::istream &operator>>(std::istream &is, Empresa &emp)
{
    do
    {
        std::cout << "\nDigite o nome da empresa: ";
        is >> emp.m_nome;
        if (emp.m_nome == "" || emp.m_nome == " ")
        {
            std::cout << "Estes valores não são válidos!";
        };
    } while (emp.m_nome == "" || emp.m_nome == " ");

    bool isGoodCnpj = false;
    while (!isGoodCnpj)
    {
        std::cout << "Digite, com apenas números, o CNPJ da [" << emp.m_nome << "] : ";
        std::string valor;
        is >> valor;
        isGoodCnpj = emp.trySetCnpj(valor);
    }

    return is;
}