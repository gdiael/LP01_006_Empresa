#include "funcionario.h"
#include "empresa.h"

Empresa::Empresa(std::string nome, std::string cnpj):m_nome(nome), m_cnpj(cnpj)
{
    m_totalFuncionarios = 0;
}

Empresa::~Empresa(){}

void Empresa::addFuncionario(Funcionario *novoFunc)
{
    if(m_totalFuncionarios == MAX_FUNCIONARIOS){
        std::cerr << "A empresa já está lotada!" << std::endl;
    }else{
        bool canAdd = true;
        for(int i=0; (canAdd && i < m_totalFuncionarios ); i++){
            if(*m_funcionarios[i] == *novoFunc){
                canAdd = false;
            };
        };
        if(canAdd){
            m_funcionarios[m_totalFuncionarios++] = novoFunc;
        }else{
            std::cerr << "O funcionário já foi adicionado!" << std::endl;
        };
    };
}

void Empresa::concederAumento(double aumento)
{

}

int Empresa::getTotalFuncionarios()
{
    return m_totalFuncionarios;
}

void Empresa::operarRh()
{

}

void Empresa::printFuncionarios()
{
    for(int i = 0; i < m_totalFuncionarios ; i++){
        std::cout << *m_funcionarios[i];
    }
}