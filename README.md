# LP01_006_Empresa
## Objetivo
Foi solicitado na disciplina de Linguagem de Programação I, do curso de Bacharelado em TI da UFRN que desenvolvessemos um programa em C++ para implementação das classes Funcionario e Empresa, onde:
- A classe Funcionario deveria ter obrigatoriamente:
    - Membros para representar o `nome` do funcionário e seu `salário`.
    - A sobrecarga do operador de igualdade `==` para comparação entre objetos desde tipo.
    - A sobrecarga do operador de extração `>>` para leitura dos dados de um novo funcionário.
- A classe Empresa deveria ter obrigatoriamente:
    - Membros para representar o `nome` da empresa e seu `CNPJ`.
    - Membro que representasse uma lista de funcionários.
    - Método para adicionar novos funcionários a lista de funcionários, tomando cuidado para não adicionar funcionários repetidos e mostrando uma mensagem de erro quando o usuário o tentasse.
    - A sobrecarga do operador de inserção `<<` para a implementação de uma listagem dos dados de todos os funcionários da empresa.
    - Método que implemente um aumento de salário de todos os funcionários da empresa.
    - Método para listagem da média salarial da empresa.
## A metodologia empregada
Além das diretrizes estipuladas pelo Professor, tambem adotei as especificações abaixo para que o programa ficasse melhor apresentado e com uma execução mais confiável:
- Implementação de uma função para converter uma string em Caixa Alta (maiúsculo), para fazer comparações de strings do tipo *caseinsensitive*, o objetivo disso foi o de evitar o cadastro de dois funcionários com nomes como João e joão, mas também foi usada para verificar alguns outros tipos de entrada do usuário.
- Implementação de verificações para inpedir que o usuário fornecesse valores incoerentes como os membros, como salário e CNPJ.
- Implementação também de um método de remoção de um funcionário da lista defuncionários.

Para realização das operações na lista de funcionarios [Adicionar, Deletar e Conceder aumento] e para realização das operações de listagem [Listagem dos funcionários e da média salarial] e o *Exit* do programa foi implementado um método publico na classe Empresa, que chamei de operarRh, este método informa um conjunto de possíveis entradas em comando de linha que podem ser usadas pelo usuário para realizar as operações, as chaves dessas entradas foram inseridas em um membro estático da classe Empresa, do tipo array de string.
## Execução do programa
Na execução do programa é solicitado ao usuário o nome de uma empresa e seu respectivo CNPJ, sendo tratadas entradas consideradas inválidas, tanto para o nome [p.e. strings do tipo " "] quando para o CNPJ [p.e. strings do tipo "asdas12"], em seguida é fornecido ao mesmo, um conjunto de possíveis entradas:
> [Aumento/Contratar/Demitir/Listar/Media/Sair]

Onde:
- **Aumento**: O usuário informará uma porcentagem de aumento para todos os funcionários da empresa.
    - Em seguida será impressa uma mensagem caso o aumento tenha dado certo.
    - Caso não existam funcionários na array, será exibida uma mensagem de erro.
- **Contratar**: O usuáro deverá informar o nome e salário do novo funcionário a ser contratado.
    - Caso já exista um funcionário contratado com o nome informado, será mostrada uma mensagem de erro.
    - Não serão aceitos salários inferiores ao salário mínimo [R$ 956,00]
- **Demitir**: O usuário informará o nome do funcionário a ser demitido:
    - Será exibida uma mensagem de erro caso não existam funcionários na lista.
    - Será exibida uma mensagem de erro caso o não exista funcionário com o nome informado.
- **Listar**: Exibirá uma listagem dos dados da empresa no formato:
    ```
      Empresa: Bradesco [CNPJ: 12.300.555/0001-90]
      Constituída por 3 funcionários, à saber:
        Raimundo           [R$  2420.00]
        Tereza             [R$  1210.00]
        Breno Ferreira     [R$  1815.61]
      Pagamos, em media    [R$  1815.20]
    ```
    - Caso a lista de funcionários tenha apenas um membro, não será exibida a ultima linha.
    - Caso a lista de funcionários esteja vazia a mensagem será um pouco diferente.
- **Media**: Exibirá a média salarial da empresa.
    - Caso a lista de funcionários esteja vazia, mostrará uma mensagem de erro.
- **Sair**: Encerá a execução do programa.