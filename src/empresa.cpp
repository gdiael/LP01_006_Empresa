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

Empresa::Empresa() : m_nome("FulanoSA"), m_cnpj("00000000000000"), m_totalFuncionarios(0) {}

Empresa::~Empresa() {}

std::string Empresa::m_rhKeyList[RH_KEYS] = {"Aumento", "Contratar", "Demitir", "Listar", "Sair"};

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
    std::string cnpjFormatar = m_cnpj;
    cnpjFormatar.insert(12, "-");
    cnpjFormatar.insert(8, "/");
    cnpjFormatar.insert(5, ".");
    cnpjFormatar.insert(2, ".");
    return cnpjFormatar;
}

bool Empresa::trySetCnpj(std::string cnpj)
{
    int size = cnpj.size();

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

    if (size != 14)
    {
        std::cout << "O CNPJ precisa ter 14 caracteres numéricos exatamente!" << std::endl;
        return false;
    };

    m_cnpj = cnpj;
    return true;
}

bool Empresa::addFuncionario(Funcionario *novoFunc)
{
    if (m_totalFuncionarios == MAX_FUNCIONARIOS)
    {
        std::cerr << "A empresa já está lotada!" << std::endl;
        return false;
    }

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
        std::cout << novoFunc->getNome() << " entrou no quadro da empresa " << m_nome << "!" << std::endl;
        return true;
    }
    else
    {
        std::cerr << novoFunc->getNome() << " já faz parte da empresa " << m_nome << "!" << std::endl;
        return false;
    };
}

bool Empresa::delFuncionario(std::string funcNome)
{
    if (m_totalFuncionarios == 0)
    {
        std::cout << "Não existem funcionários na empresa!" << std::endl;
        return false;
    };
    // vamos criar um funcionário auxiliar para fazer a comparação com os outros
    Funcionario *aux = new Funcionario(funcNome, MIN_SALARIO);
    // toDel vai guardar o indice do funcinário a ser excluído
    // caso ele continue como -1, significa que não existe nenhum funcionário
    // com o nome igual ao que está salvo na variável funcNome
    int toDel = -1;
    // procurar na array de funcionários o funcionário que tenha o nome igual a funcNome
    for (int i = 0; i < m_totalFuncionarios; i++)
    {
        if (*m_funcionarios[i] == *aux)
        {
            toDel = i;
        };
    };
    // caso exista um funcionário com o nome funcNome pegaremos o ultimo funcionário da array
    // e colocaremos em sua posição [caso este já seja o ultimo elemento não fará diferênça]
    // em seguida reduziremos a quantidade total de funcionários cadastrados
    if (toDel > -1)
    {
        m_funcionarios[toDel] = m_funcionarios[m_totalFuncionarios - 1];
        m_totalFuncionarios--;
        std::cout << "O funcionário " << funcNome << " saiu do quadro da empresa " << m_nome << "!" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "O funcionário " << funcNome << " não faz parte da empresa " << m_nome << "!" << std::endl;
        return false;
    };
}

void Empresa::concederAumento(double fatorDeAumento)
{
    for (int i = 0; i < m_totalFuncionarios; i++)
    {
        double salario = m_funcionarios[i]->getSalario();
        m_funcionarios[i]->setSalario(salario * (1.0 + fatorDeAumento));
    };
}

double Empresa::getMediaSalarial()
{
    double mediaSalarios = 0.0;
    for (int i = 0; i < m_totalFuncionarios; i++)
    {
        mediaSalarios += m_funcionarios[i]->getSalario();
    };
    mediaSalarios = mediaSalarios / m_totalFuncionarios;
    return mediaSalarios;
}

void Empresa::operarRh()
{
    std::cout << "Você agora é o chefe do RH da empresa " << m_nome << "." << std::endl;
    bool isOpen = true;
    while (isOpen)
    {
        std::cout << "O que deseja fazer [";
        for (std::string key : m_rhKeyList)
        {
            std::cout << key << "/";
        };
        std::cout << "]? ";
        std::string prompt;
        std::getline(std::cin, prompt);
        prompt = str_toupper(prompt);
        if (prompt == str_toupper(m_rhKeyList[0]))
        {
            if (m_totalFuncionarios > 0)
            {
                bool isGoodValor = false;
                double aumento = -1.0;
                while (!isGoodValor)
                {
                    std::cout << "Digite a porcentagem de aumento a ser aplicado: ";
                    std::string valor;
                    std::getline(std::cin, valor);
                    try
                    {
                        aumento = std::stod(valor);
                        if (aumento <= 0.0)
                        {
                            std::cout << "O aumento precisa ser um valor maior que zero!" << std::endl;
                        }
                        else
                        {
                            isGoodValor = true;
                        };
                    }
                    catch (std::exception &ia)
                    {
                        std::cout << "O aumento precisa ser um valor numérico!" << std::endl;
                    };
                };
                concederAumento(aumento / 100.0);
            }
            else
            {
                std::cout << "O quadro da empresa está vazio, não é possível conceder aumentos!" << std::endl;
            };
        }
        else if (prompt == str_toupper(m_rhKeyList[1]))
        {
            Funcionario *novo = new Funcionario;
            std::cin >> *novo;
            addFuncionario(novo);
        }
        else if (prompt == str_toupper(m_rhKeyList[2]))
        {
            if (m_totalFuncionarios == 0)
            {
                std::cout << "O quadro da empresa está vazio, não é possível fazer demissões!" << std::endl;
            }
            else
            {
                std::string funcName = Funcionario::askForName(std::cin, "Nome do funcionário a ser demitido");
                delFuncionario(funcName);
            }
        }
        else if (prompt == str_toupper(m_rhKeyList[3]))
        {
            std::cout << *this << std::endl;
        }
        else if (prompt == str_toupper(m_rhKeyList[4]))
        {
            isOpen = false;
        }
        else
        {
            std::cout << "Opção inválida! Tente novamente." << std::endl;
        };
    };
}

std::ostream &operator<<(std::ostream &os, Empresa &emp)
{
    os << "\nEmpresa: " << emp.m_nome << " [CNPJ: " << emp.getCnpj() << "]" << std::endl;
    if (emp.m_totalFuncionarios == 0)
    {
        os << "Nesse momento, nosso quadro de funcionários encontra-se vazio." << std::endl;
        return os;
    }
    os << "Constituída por " << emp.m_totalFuncionarios;
    os << (emp.m_totalFuncionarios == 1 ? " funcionário" : " funcionários") << ", à saber:" << std::endl;
    for (int i = 0; i < emp.m_totalFuncionarios; i++)
    {
        os << "   " << *emp.m_funcionarios[i];
    };
    if (emp.m_totalFuncionarios > 1)
    {
        os << " " << std::left << std::setw(20) << "Pagamos, em media";
        os << " [R$ " << std::setprecision(2) << std::fixed;
        os << std::right << std::setw(8) << emp.getMediaSalarial() << "]" << std::endl;
    };
    return os;
}

std::istream &operator>>(std::istream &is, Empresa &emp)
{
    bool isGoodNome = false;
    while (!isGoodNome)
    {
        std::cout << "\nDigite o nome da empresa: ";
        std::string nome;
        std::getline(is, nome);
        if (nome != "" && nome != " ")
        {
            isGoodNome = true;
        };
        if (isGoodNome)
        {
            emp.m_nome = nome;
        }
        else
        {
            std::cout << "Estes valores não são válidos!";
        };
    };

    bool isGoodCnpj = false;
    while (!isGoodCnpj)
    {
        std::cout << "Digite, com apenas números, o CNPJ da empresa [" << emp.m_nome << "] : ";
        std::string valor;
        std::getline(is, valor);
        isGoodCnpj = emp.trySetCnpj(valor);
    }

    return is;
}