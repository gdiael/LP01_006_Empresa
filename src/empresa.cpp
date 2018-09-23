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

std::string Empresa::m_rhKeyList[RH_KEYS] = {"Aumento", "Contratar", "Demitir", "Listar", "Media", "Sair"};

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
    // O valor presento no membro m_cnpj será obrigatoriamento do formato:
    // 11222333000155
    // ele então será retornado no formato
    // 11.222.333/0001-55
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
    // esta variável será usada para verificar se os caracteres passados em cnpj são apenas numericos
    std::string numList = "0123456789";
    for (int i = 0; i < size; i++)
    {
        char c = cnpj[i];
        // o método std::string::find retona o indice do caractere ou -1, caso o caractere não esteja presente
        if (numList.find(c) == std::string::npos)
        {
            // se incontramos um caractere não numerico, mostrando a mensagem de erro e saimos do métido
            std::cerr << "Dígite apenas números!" << std::endl;
            return false;
        };
    }
    // o cnpj deve ter exatamente 14 digitos numéricos
    if (size != 14)
    {
        std::cout << "O CNPJ precisa ter 14 caracteres numéricos exatamente!" << std::endl;
        return false;
    };
    // se a execução chegar até aqui significa que está tudo OK
    m_cnpj = cnpj;
    return true;
}

bool Empresa::addFuncionario(Funcionario *novoFunc)
{
    if (m_totalFuncionarios == MAX_FUNCIONARIOS)
    {
        // mensagem de erro ao chegar no limite de alocão do membro m_funcionarios
        std::cerr << "A empresa já está lotada!" << std::endl;
        return false;
    }

    bool canAdd = true;
    for (int i = 0; (canAdd && i < m_totalFuncionarios); i++)
    {
        // verificação em todos os membros da array de funcionarios de algum bate a condição
        // o operador faz uma verificação caseinsensitive, ou seja ("João" == "joão") vai retornar true
        if (*m_funcionarios[i] == *novoFunc)
        {
            canAdd = false;
        };
    };
    // se pasarmos nas verificações, depois adicionar o nome funcionário
    if (canAdd)
    {
        // fazemos a atribuição e incrementação o número do funcionários ao mesmo tempo com o pós-incremento
        m_funcionarios[m_totalFuncionarios++] = novoFunc;
        // mensagem de confirmação, mostrando que o funcionário foi adicionado corretamente
        std::cout << novoFunc->getNome() << " entrou no quadro da empresa " << m_nome << "!" << std::endl;
        return true;
    }
    else
    {
        // mensagem de erro, mostrando que já existe um funcionário com o mesmo nome.
        std::cerr << "Não foi possível contratar " << novoFunc->getNome() << ", pois já faz parte da empresa " << m_nome << "!" << std::endl;
        return false;
    };
}

bool Empresa::delFuncionario(std::string funcNome)
{
    if (m_totalFuncionarios == 0)
    {
        std::cerr << "Não existem funcionários na empresa!" << std::endl;
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

void Empresa::concederAumento()
{
    // para continua precisa ter pelo menos um funcionário, se não, mostra mensagem de erro
    if (m_totalFuncionarios > 0)
    {
        bool isGoodValor = false;
        double aumento = -1.0;
        // enquanto o usuário não digitar um valor válido, continue executando
        while (!isGoodValor)
        {
            std::cout << "Digite a porcentagem de aumento a ser aplicada: ";
            std::string valor;
            std::getline(std::cin, valor);
            // usamos o try para tentar a converção do valor passar na string para o tipo double
            // assim caso o usuário insira um valor não numérico o programa não é afetado pelo erro
            // e podemos exibir uma mensagem de explicação
            try
            {
                aumento = std::stod(valor);
                if (aumento <= 0.0)
                {
                    std::cerr << "O aumento precisa ser um valor maior que zero!" << std::endl;
                }
                else
                {
                    isGoodValor = true;
                };
            }
            catch (std::exception &ia)
            {
                std::cerr << "O aumento precisa ser um valor numérico!" << std::endl;
            };
        };
        // dividimos o valor por 100.0 para ser convertido em porcentagem decimal
        aumento = aumento / 100.0;
        // vamos adicionar o aumento em todos os funcionarios presentes na array
        for (int i = 0; i < m_totalFuncionarios; i++)
        {
            m_funcionarios[i]->giveAumentoSalario(aumento);
        };
        std::cout << "Foi concedido um aumento salarial de " << std::setprecision(1) << std::fixed;
        std::cout << (aumento * 100.0) << "%!" << std::endl;
    }
    else
    {
        std::cerr << "O quadro da empresa está vazio, não é possível conceder aumentos!" << std::endl;
    };
}

double Empresa::getMediaSalarial()
{
    double mediaSalarios = 0.0;
    // vamos somar os salarios de todos os funcionarios
    for (int i = 0; i < m_totalFuncionarios; i++)
    {
        mediaSalarios += m_funcionarios[i]->getSalario();
    };
    // e dividir pela quantidade
    mediaSalarios = mediaSalarios / m_totalFuncionarios;
    return mediaSalarios;
}

void Empresa::operarRh()
{
    std::cout << "Você agora é o chefe do RH da empresa " << m_nome << "." << std::endl;
    bool isOpen = true;
    // o valor isOpen só sera modificado quando o usuário digitar "Sair"
    while (isOpen)
    {
        // vamos imprimir cada opção de comando disponível para o usuário
        std::cout << "O que deseja fazer [";
        for (std::string key : m_rhKeyList)
        {
            std::cout << key << "/";
        };
        std::cout << "]? ";
        std::string prompt;
        std::getline(std::cin, prompt);
        // converte o prompt do usuário em maiúsculas
        prompt = str_toupper(prompt);
        // caso seja "Aumento"
        if (prompt == str_toupper(m_rhKeyList[0]))
        {
            concederAumento();
        }
        // caso seja "Contratar"
        else if (prompt == str_toupper(m_rhKeyList[1]))
        {
            Funcionario *novo = new Funcionario;
            std::cin >> *novo;
            addFuncionario(novo);
        }
        // caso seja "Demitir"
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
        // caso seja "Listar"
        else if (prompt == str_toupper(m_rhKeyList[3]))
        {
            std::cout << *this << std::endl;
        }
        // caso seja "Media"
        else if (prompt == str_toupper(m_rhKeyList[4]))
        {
            if (m_totalFuncionarios > 0)
            {
                double media = getMediaSalarial();
                std::cout << "A media salarial da empresa " << m_nome << " é de R$ ";
                std::cout << std::setprecision(2) << std::fixed << media << std::endl;
            }
            else
            {
                std::cerr << "Não é possível calcular a média salarial, pois o quadro da empresa " << m_nome << " está vazio!" << std::endl;
            };
        }
        // caso seja "Sair"
        else if (prompt == str_toupper(m_rhKeyList[5]))
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
        // a impressão dos dados do funcionário é responsabilidade da referida classe
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
    // adaptação do método estático da classe funcionário para esta tarefa
    emp.m_nome = Funcionario::askForName(is,"Digite o nome da empresa");
    
    bool isGoodCnpj = false;
    while (!isGoodCnpj)
    {
        std::cout << "Digite, com apenas números, o CNPJ da empresa [" << emp.m_nome << "] : ";
        std::string valor;
        std::getline(is, valor);
        // o método realiza o tramento das exções e dos valóres validos
        isGoodCnpj = emp.trySetCnpj(valor);
    }

    return is;
}