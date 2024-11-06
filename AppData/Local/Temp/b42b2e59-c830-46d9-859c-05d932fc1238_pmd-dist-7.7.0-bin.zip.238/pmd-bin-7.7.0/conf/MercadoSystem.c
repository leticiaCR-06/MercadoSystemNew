#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

// Estruturas
typedef struct {
    int id;
    char nome[50];
    float preco;
} Produto;

typedef struct {
    int idProduto;
    int quantidade;
} Carrinho;

// Variáveis Globais
Produto produtos[MAX_PRODUTOS];
Carrinho carrinho[MAX_CARRINHO];
int contadorProdutos = 0;
int contadorCarrinho = 0;

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para validar ID do produto
int lerIdProduto() {
    int id;
    while (1) {
        printf("ID: ");
        if (scanf("%d", &id) == 1 && id > 0) {
            limparBufferEntrada();
            return id;
        }
        printf("ID inválido. Tente novamente.\n");
        limparBufferEntrada();
    }
}

// Função para validar nome do produto
void lerNomeProduto(char *nome) {
    while (1) {
        printf("Nome do Produto: ");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = 0; // Remove newline
        int valido = 1;
        for (int i = 0; nome[i] != '\0'; i++) {
            if (!((nome[i] >= 'A' && nome[i] <= 'Z') ||
                  (nome[i] >= 'a' && nome[i] <= 'z') || nome[i] == ' ')) {
                valido = 0;
                break;
            }
        }
        if (valido) break;
        printf("Nome inválido. Tente novamente.\n");
    }
}

// Função para validar preço do produto
float lerPrecoProduto() {
    float preco;
    while (1) {
        printf("Preço: ");
        if (scanf("%f", &preco) == 1 && preco >= 0) {
            limparBufferEntrada();
            return preco;
        }
        printf("Preço inválido. Tente novamente.\n");
        limparBufferEntrada();
    }
}

// Função para cadastrar produto
void cadastrarProduto() {
    if (contadorProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto novoProduto;
    novoProduto.id = lerIdProduto();
    lerNomeProduto(novoProduto.nome);
    novoProduto.preco = lerPrecoProduto();

    // Verificando duplicidade
    for (int i = 0; i < contadorProdutos; i++) {
        if (produtos[i].id == novoProduto.id) {
            printf("Produto com ID %d já cadastrado.\n", novoProduto.id);
            return;
        }
    }

    produtos[contadorProdutos++] = novoProduto;
    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar produtos cadastrados
void listarProdutos() {
    if (contadorProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    for (int i = 0; i < contadorProdutos; i++) {
        printf("ID: %d, Nome: %s, Preço: %.2f\n", produtos[i].id, produtos[i].nome, produtos[i].preco);
    }
}

// Função para comprar produtos
void comprarProdutos() {
    if (contadorProdutos == 0) {
        printf("Nenhum produto disponível para compra.\n");
        return;
    }

    int idProduto, quantidade;
    listarProdutos();

    printf("Digite o ID do produto que deseja comprar: ");
    scanf("%d", &idProduto);

    // Verificar se o produto existe
    int encontrado = 0;
    for (int i = 0; i < contadorProdutos; i++) {
        if (produtos[i].id == idProduto) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Produto não encontrado.\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    // Adicionando ao carrinho
    for (int i = 0; i < contadorCarrinho; i++) {
        if (carrinho[i].idProduto == idProduto) {
            carrinho[i].quantidade += quantidade;
            printf("Quantidade atualizada no carrinho.\n");
            return;
        }
    }

    carrinho[contadorCarrinho].idProduto = idProduto;
    carrinho[contadorCarrinho].quantidade = quantidade;
    contadorCarrinho++;
    printf("Produto adicionado ao carrinho.\n");
}

// Função para visualizar carrinho
void visualizarCarrinho() {
    if (contadorCarrinho == 0) {
        printf("Seu carrinho está vazio.\n");
        return;
    }

    for (int i = 0; i < contadorCarrinho; i++) {
        for (int j = 0; j < contadorProdutos; j++) {
            if (produtos[j].id == carrinho[i].idProduto) {
                printf("Produto: %s, Quantidade: %d, Preço: %.2f\n",
                       produtos[j].nome, carrinho[i].quantidade, produtos[j].preco);
            }
        }
    }
}

// Função para finalizar compra
void fecharCompra() {
    if (contadorCarrinho == 0) {
        printf("Carrinho vazio. Não é possível finalizar a compra.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < contadorCarrinho; i++) {
        for (int j = 0; j < contadorProdutos; j++) {
            if (produtos[j].id == carrinho[i].idProduto) {
                total += produtos[j].preco * carrinho[i].quantidade;
            }
        }
    }

    printf("Compra finalizada. Total: %.2f\n", total);
    contadorCarrinho = 0; // Limpar carrinho após compra
}

// Função para reiniciar o sistema
void restart() {
    contadorProdutos = 0;
    contadorCarrinho = 0;
    printf("Sistema reiniciado.\n");
}

// Função do menu principal
void menu() {
    int opcao;
    do {
        printf("\nEscolha uma opção:\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Comprar Produtos\n");
        printf("4 - Visualizar Carrinho\n");
        printf("5 - Finalizar Compra\n");
        printf("0 - Reiniciar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: comprarProdutos(); break;
            case 4: visualizarCarrinho(); break;
            case 5: fecharCompra(); break;
            case 0: restart(); break;
            default: printf("Opção inválida. Tente novamente.\n"); break;
        }
    } while (opcao != 0);
}

// Função main
int main() {
    menu();
    return 0;
}
