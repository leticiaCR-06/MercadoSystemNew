PLANO DE REFATORAÇÃO DO CÓDIGO DO SISTEMA DE MERCADO

 1. Melhoria da Legibilidade
- Renomeação de Funções e Variáveis:
  Algumas funções e variáveis têm nomes que não são intuitivos. Renomeá-las para algo mais descritivo ajudará a melhorar a legibilidade.
    -`produtoJaCadastrado` → `verificarProdutoDuplicado`: O nome atual não transmite claramente que está verificando duplicatas de produto pelo nome ou ID.
  - `cadastrarProduto` → `adicionarProduto`: Reflete melhor o objetivo da função de adicionar um produto ao inventário.
  - `limparBufferEntrada` → `limparEntradaBuffer`: Nome mais claro e melhor legibilidade.
  - Melhorar a formatação:  
  - Usar espaçamento consistente entre blocos de código e evitar funções longas que podem ser separadas.
- Adicionar comentários explicativos em pontos críticos do código. Não é necessário comentar cada linha, mas fornecer explicações claras para funções complexas e trechos críticos.

 2. Melhoria da Manutenibilidade 
- Evitar a duplicação de código:
  Há várias seções do código onde a mesma lógica é repetida. Por exemplo, as funções que lêem entradas do usuário, como `cadastrarProduto` e `comprarProdutos`, possuem códigos repetidos para validar as entradas. Podemos criar uma função genérica para validação de entrada.
- Nova Função: Criar uma função genérica para entrada que verifica se o valor inserido pelo usuário é válido. Podendo ser usado em várias funções.
- Separação de Responsabilidades:
  Muitas funções fazem mais de uma coisa. Por exemplo, a função `listarProdutos` realiza a listagem de produtos e oferece a opção de alteração. Podemos separar a listagem da lógica de alteração.
Refatoração: Dividir a função `listarProdutos` em duas funções:
  - `listarProdutos()`: Responsável apenas por listar os produtos.
  - `alterarProdutoNoCarrinho()`: Responsável apenas por alterar o produto no carrinho, removendo a lógica do menu de `listarProdutos`.
- Reorganização das funções de Menu:
  O código de escolha no menu (`menu()`) pode ser simplificado em uma estrutura mais modular. Cada item do menu pode ser uma função separada, permitindo um código mais limpo e fácil de manter.

3. Melhoria no Desempenho
   
 Embora o código atual não tenha grandes problemas de desempenho, existem pequenas mudanças que podem melhorar a performance, especialmente ao lidar com grandes volumes de produtos e carrinhos.
- Reduzir as buscas lineares:
  O código atual realiza buscas lineares em arrays, como em `produtoJaCadastrado` e `comprarProdutos`. Se o número de produtos e itens no carrinho crescer significativamente, o desempenho será impactado. 
 Uma maneira de melhorar isso seria utilizar estruturas de dados mais eficientes, como listas ligadas ou tabelas hash, para realizar buscas mais rápidas. No entanto, como o número de itens é limitado a 50, isso pode não ser uma grande prioridade, mas vale considerar caso o número de produtos aumente.
- Uso de `switch-case` para grandes opções:
  Em vez de usar vários `if` e `else`, utilizar o `switch-case` nas opções do menu pode proporcionar um pequeno ganho de desempenho, além de tornar o código mais legível.

4. Refatorar Funções Complexas
   
- Divisão de Funções: Identificar funções com muitas responsabilidades e dividi-las em funções menores, cada uma com uma responsabilidade única. Isso também reduz a complexidade ciclomática, que é a medida do número de caminhos independentes em uma função. Funções com alta complexidade ciclomática são mais propensas a erros e difíceis de testar.

 Exemplo: A função cadastrarProduto realiza muitas tarefas: ler entradas do usuário, validar essas entradas e registrar o produto. Podemos dividir isso em várias funções menores:
	lerEntradaProduto: função responsável apenas por ler os dados do produto.
	validarProduto: função que valida a entrada do produto.
	adicionarProduto: função que efetivamente adiciona o produto ao sistema

5. Melhorar Segurança
   
A segurança é uma consideração essencial para qualquer aplicação. Mesmo que o código não envolva diretamente a manipulação de dados sensíveis, a validação de entradas e o uso adequado de variáveis globais são práticas importantes para garantir que o sistema seja seguro e resistente a falhas.
- Validação de Entradas: Embora o código já possua validações simples, podemos melhorar a segurança de forma geral validando mais entradas, incluindo:
Evitar injeção de dados maliciosos: Certificar-se de que as entradas não permitam dados inesperados ou maliciosos.

Verificação de tipo e limite: Implementar verificações rigorosas para entradas como ID, nome e preço, garantindo que valores inválidos ou perigosos não sejam inseridos.

 Exemplo:
ID do Produto: Garantir que o ID seja sempre um número positivo, dentro de um intervalo seguro.

°Nome do Produto: Evitar que caracteres especiais ou não alfanuméricos sejam inseridos, o que poderia afetar a integridade do sistema ou causar falhas.
Limitação do uso de Variáveis Globais: O código atual faz uso de variáveis globais como produtos, carrinho e contadorProdutos, que tornam o código mais difícil de depurar e testar, além de aumentar o risco de erros inesperados. A refatoração pode envolver:

°Passar dados como parâmetros: Em vez de acessar diretamente variáveis globais dentro de funções, podemos passar esses dados como parâmetros para reduzir o escopo de variáveis globais.
Usar estruturas ou classes: Para melhor encapsulamento, podemos agrupar as variáveis associadas em uma estrutura ou classe, criando um contexto claro para cada conjunto de dados, como um Objeto Carrinho ou Produto.


