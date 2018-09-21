#include "empresa.h"
#include "funcionario.h"

int main(int argc, char const *argv[])
{
    std::cout << "\n\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    std::cout << "|||Programa para a demonstração da implementação das Classes: Empresa e Funcionário.|||" << std::endl;
    std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n" << std::endl;
    
    Empresa jbs;
    std::cin >> jbs;
    Funcionario novo;
    std::cin >> novo;
    Funcionario out;
    std::cin >> out;
    jbs.addFuncionario(&novo);
    jbs.addFuncionario(&out);
    std::cout << jbs;
    
    return 0;
}
