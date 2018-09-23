#include "funcionario.h"

Funcionario::Funcionario(std::string nome, double salario) : m_nome(nome), m_salario(salario) {}

Funcionario::Funcionario() : m_nome(""), m_salario(0.0) {}

Funcionario::~Funcionario() {}

std::string Funcionario::askForName(std::istream &is, std::string mensagem)
{
    std::string nome;
    std::cout << "\n" << mensagem << ": ";
    std::getline(is, nome);
    if (nome != "" && nome != " ")
    {
        return nome;
    }else{
        std::cout << "Estes valores não são válidos!";
        return askForName(is, mensagem);
    };
}

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

bool Funcionario::trySetSalario(std::string valor)
{
    double salario = 0.0;
    try
    {
        salario = std::stod(valor);
    }
    catch (std::exception &ia)
    {
        std::cout << "O salário precisa ser um valor numérico!" << std::endl;
        return false;
    };
    if (salario < MIN_SALARIO)
    {
        std::cout << "O salário não pode ser inferior ao salário mínimo (R$ " << MIN_SALARIO << ")!!!\n";
        return false;
    }
    else
    {
        m_salario = salario;
    };
    return true;
}

bool Funcionario::operator==(Funcionario &outro)
{
    return (str_toupper(m_nome) == str_toupper(outro.getNome()));
}

std::istream &operator>>(std::istream &is, Funcionario &func)
{
    func.m_nome = Funcionario::askForName(is, "Digite o nome do novo Funcionário");
    
    bool isGoodWage = false;
    while (!isGoodWage)
    {
        std::cout << "Digite o salário de [" << func.m_nome << "] : ";
        std::string valor;
        std::getline(is, valor);
        isGoodWage = func.trySetSalario(valor);
    };

    return is;
}

std::ostream &operator<<(std::ostream &os, Funcionario &func)
{
    // aqui serão usados manipuladores para formatar a saída
    // o nome do funcionário será ajustado a esquerda, e terá um espaçamento de 15
    // caracteres antes do salário
    os << std::left << std::setw(18) << func.m_nome;
    // o salário será formatado com duas casas decimais
    os << " [R$ " << std::setprecision(2) << std::fixed;
    // será ajustado a direita com espaçamento de 8 caracteres
    os << std::right << std::setw(8) << func.m_salario << "]" << std::endl;
    return os;
}

std::string str_toupper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
      [](unsigned char c){ return std::toupper(c); }
    );
    return s;
}