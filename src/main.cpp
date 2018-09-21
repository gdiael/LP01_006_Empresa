#include "empresa.h"
#include "funcionario.h"

int main(int argc, char const *argv[])
{
    Empresa jbs("JBS", "000234/0001");
    Funcionario novo;
    std::cin >> novo;
    Funcionario out;
    std::cin >> out;
    jbs.addFuncionario(&novo);
    jbs.addFuncionario(&out);
    jbs.printFuncionarios();
    /* code */
    return 0;
}
