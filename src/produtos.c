#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "produtos.h"

const char *db_produtos = "data/db_produtos.csv";
int totalProdutos = 29;

static void salvarProduto(Produto produto) {
    const char *db_produtos = "produtos.csv";

    FILE *arquivo = fopen(db_produtos, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(
        arquivo, 
        "%s,%s,%s,%s,%.2f,%d\n", 
        produto.categoria, 
        produto.tipoAnimal, 
        produto.marca, 
        produto.descricao, 
        produto.preco, 
        produto.estoque
    );

    fclose(arquivo);

    printf("\nProduto cadastrado com sucesso!\n");
}
// Implementação das funções do módulo produtos

static void cadastrarProduto(){
    Produto newProduto;
    
    if (totalProdutos >= 200) {
 printf("Capacidade m�xima de produtos atingida.\n");
    return;
    }

    printf("Digite a categoria do produto: ");
    setbuf(stdin, NULL);
    fgets(newProduto.categoria, 50, stdin);
    newProduto.categoria[strcspn(newProduto.categoria, "\n")] = 0;
    printf("Digite o tipo de animal: ");
    setbuf(stdin, NULL);
    fgets(newProduto.tipoAnimal, 30, stdin);
    newProduto.tipoAnimal[strcspn(newProduto.tipoAnimal, "\n")] = 0;
    printf("Digite a marca do produto: ");
    setbuf(stdin, NULL);
    fgets(newProduto.marca, 50, stdin);
    newProduto.marca[strcspn(newProduto.marca, "\n")] = 0;
    printf("Digite a descri��o do produto: ");
    setbuf(stdin, NULL);
    fgets(newProduto.descricao, 100, stdin);
    newProduto.descricao[strcspn(newProduto.descricao, "\n")] = 0;
    printf("Digite o pre�o do produto: ");
    scanf("%f",&newProduto.preco);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &newProduto.estoque);

    if(strlen(newProduto.categoria) <= 1 || strlen(newProduto.descricao) <= 1  || strlen(newProduto.marca) <= 1  || strlen(newProduto.tipoAnimal) <= 1){
        printf("\nTodos os campos devem ser preenchidos com dados corretos!\n");
        return;
    }
    totalProdutos++;
    salvarProduto(newProduto);

}

static void listarProdutos() {
    
    FILE *arquivo = fopen(db_produtos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo! Verifique se ele existe e tente novamente.\n");
        return;
    }

    printf("\nLista de Produtos Cadastrados:\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("| Categoria             | Tipo Animal       | Marca              | Descrição            | Preço   | Estoque |\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Produto produto;

        // Divide a linha nos campos usando sscanf
        if (sscanf(
                linha, 
                "%49[^,],%29[^,],%49[^,],%99[^,],%f,%d",
                produto.categoria,
                produto.tipoAnimal,
                produto.marca,
                produto.descricao,
                &produto.preco,
                &produto.estoque) == 6) {
            // Exibe os dados do produto
            printf("| %-20s | %-16s | %-18s | %-20s | %7.2f | %7d |\n",
                   produto.categoria,
                   produto.tipoAnimal,
                   produto.marca,
                   produto.descricao,
                   produto.preco,
                   produto.estoque);
        }
    }

    printf("-----------------------------------------------------------------------------------------------\n");
    fclose(arquivo);
}

void alterarPreco(){
    // Implementar a função para alterar o preço de um produto
}

void atualizarEstoque(){
    // Implementar a função para atualizar o estoque de um produto
}

//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoProdutos()

void gerenciamentoProdutos(){
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    while(1){
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Alterar preço de um produto\n");
        printf("4 - Atualizar estoque de um produto\n");
        printf("0 - Voltar\n");

        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                alterarPreco();
                break;
            case 4:
                atualizarEstoque();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente!\n");
                break;
        }
    }
}