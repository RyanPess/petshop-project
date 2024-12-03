#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "produtos.h"

const char *db_produtos = "data/db_produtos.csv";
const char *arqTemp = "data/temp.csv";
int totalProdutos = 29;

static void salvarProduto(Produto produto, int idAtual);
static void cadastrarProduto();
static void listarProdutos();
static void buscarProdutoByID();
static void alterarPreco();
static void atualizarEstoque();


//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoProdutos()

void gerenciamentoProdutos(){
    //setlocale(LC_ALL, "Portuguese");
    int opcao;
    while(1){
        printf("1 - Cadastrar novo produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Buscar produto por ID\n");
        printf("4 - Alterar preco de um produto\n");
        printf("5 - Atualizar estoque\n");
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
                buscarProdutoByID();
                break;
            case 4:
                alterarPreco();
                break;
            case 5:
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

static void salvarProduto(Produto produto, int idAtual) {

    FILE *arquivo = fopen(db_produtos, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(
        arquivo, 
        "%d,%s,%s,%s,%s,%.2f,%d\n", 
        idAtual,
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

static void cadastrarProduto() {
    Produto newProduto;

    // Verificando o total de produtos cadastrados no arquivo
    FILE *arquivo = fopen(db_produtos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    int contadorProdutos = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        contadorProdutos++;
    }
    fclose(arquivo);
    
    if (contadorProdutos >= 200) {
        printf("Capacidade máxima de produtos atingida.\n");
        return;
    }

    // Recebendo as informações do produto
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
    printf("Digite a descrição do produto: ");
    setbuf(stdin, NULL);
    fgets(newProduto.descricao, 100, stdin);
    newProduto.descricao[strcspn(newProduto.descricao, "\n")] = 0;
    printf("Digite o preço do produto: ");

    while (scanf("%f", &newProduto.preco) != 1 || newProduto.preco <= 0) {
        printf("Preço inválido. Digite novamente: ");
        setbuf(stdin, NULL); // Limpar o buffer do teclado
    }

    printf("Digite a quantidade em estoque: ");
    while (scanf("%d", &newProduto.estoque) != 1 || newProduto.estoque < 0) {
        printf("Quantidade inválida. Digite novamente: ");
        setbuf(stdin, NULL);
    }

    if (strlen(newProduto.categoria) <= 1 || strlen(newProduto.descricao) <= 1 || 
        strlen(newProduto.marca) <= 1 || strlen(newProduto.tipoAnimal) <= 1) {
        printf("\nTodos os campos devem ser preenchidos com dados corretos!\n");
        return;
    }

    totalProdutos++;
    salvarProduto(newProduto, totalProdutos);
}

static void listarProdutos() {
    FILE *arquivo = fopen(db_produtos, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo! Verifique se ele existe e tente novamente.\n");
        return;
    }

    printf("\nLista de Produtos Cadastrados:\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("|   ID    | Categoria             | Tipo Animal       | Marca              | Descrição            | Preço   | Estoque |\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Produto produto;

        // Divide a linha nos campos usando sscanf
        if (sscanf(linha, "%d,%49[^,],%29[^,],%49[^,],%99[^,],%f,%d", 
                    &produto.id, produto.categoria, produto.tipoAnimal, 
                    produto.marca, produto.descricao, &produto.preco, 
                    &produto.estoque) == 7) {
            // Exibe os dados do produto
            printf("| %7d | %-20s | %-16s | %-18s | %-20s | %7.2f | %7d |\n", 
                    produto.id, produto.categoria, produto.tipoAnimal, 
                    produto.marca, produto.descricao, produto.preco, produto.estoque);
        }
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");

    fclose(arquivo);
}

static void buscarProdutoByID(){
    int id;
    Produto produto;
    
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    if (id <= 0) {
        printf("ID inválido!\n");
        return;
    }
    
    bool encontrado = false;
    FILE *arquivo = fopen(db_produtos, "r");
    FILE *temp = fopen(arqTemp, "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo)!= NULL) {
        sscanf(buffer, "%d,%49[^,],%29[^,],%49[^,],%99[^,],%f,%d", 
            &produto.id, produto.categoria, produto.tipoAnimal, 
            produto.marca, produto.descricao, &produto.preco, 
            &produto.estoque);
        
        if (produto.id == id) {
            encontrado = true;
            printf("\n::::::::::Produto encontrado::::::::::\n");
            printf("id: %d\n", produto.id);
            printf("Categoria: %s\n", produto.categoria);
            printf("Tipo Animal: %s\n", produto.tipoAnimal);
            printf("Marca: %s\n", produto.marca);
            printf("Descrição: %s\n", produto.descricao);
            printf("Preço: %.2f\n", produto.preco);
            printf("Estoque atual: %d\n", produto.estoque);
            printf("----------------------------------------\n\n");
            break;
        }
    }
        if (!encontrado) {
        printf("Produto com ID %d não encontrado.\n", id);
        remove(arqTemp);
        } else {
        remove(db_produtos);
        rename(arqTemp, db_produtos);
        }
}

static void alterarPreco() {
    Produto produto;
    int id;
    float novoPreco;

    FILE *arquivo = fopen(db_produtos, "r");
    FILE *temp = fopen(arqTemp, "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do produto para alterar o preço: ");
    scanf("%d", &id);

    char buffer[256];
    bool encontrado = false;

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        sscanf(buffer, "%d,%49[^,],%29[^,],%49[^,],%99[^,],%f,%d", 
            &produto.id, produto.categoria, produto.tipoAnimal, 
            produto.marca, produto.descricao, &produto.preco, 
            &produto.estoque);
        
        if (produto.id == id) {
            encontrado = true;
            printf("Produto selecionado: %s, %s\n", produto.marca, produto.descricao);
            printf("Preço atual: %.2f\n", produto.preco);
            printf("Digite o novo preço: ");
            setbuf(stdin, NULL);
            while (scanf("%f", &novoPreco) != 1 || novoPreco <= 0) {
                printf("Preço inválido. Digite novamente: ");
                setbuf(stdin, NULL);
            }

            produto.preco = novoPreco;
            printf("Preço atualizado com sucesso para %.2f!\n", produto.preco);
        }

        // Escreve no arquivo temporário, independentemente de ser alterado
        fprintf(temp, "%d,%s,%s,%s,%s,%.2f,%d\n", produto.id, produto.categoria, 
                produto.tipoAnimal, produto.marca, produto.descricao, 
                produto.preco, produto.estoque);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Produto com ID %d não encontrado.\n", id);
        remove(arqTemp);
    } else {
        remove(db_produtos);
        rename(arqTemp, db_produtos);
    }
}


static void atualizarEstoque(){
    
    Produto produto;
    int id;
    int quantidade;

    FILE *arquivo = fopen(db_produtos, "r");
    FILE *temp = fopen(arqTemp, "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    printf("Digite o ID do produto para alterar o estoque: ");
    scanf("%d", &id);

    char buffer[256];
    bool encontrado = false;

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        sscanf(buffer, "%d,%49[^,],%29[^,],%49[^,],%99[^,],%f,%d", 
            &produto.id, produto.categoria, produto.tipoAnimal, 
            produto.marca, produto.descricao, &produto.preco, 
            &produto.estoque);
        
        if (produto.id == id) {
            encontrado = true;
            printf("Produto selecionado: %s, %s\n", produto.marca, produto.descricao);
            printf("Estoque atual: %d\n", produto.estoque);
            printf("Digite a quantidade que será adicionada ao estoque: ");
            setbuf(stdin, NULL);
            while (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
                printf("Deve ser adicionado pelo menos 2. Digite novamente: ");
                setbuf(stdin, NULL);
            }

            produto.estoque += quantidade;
            printf("Estoque atualizado com sucesso, agora com %d unidades!\n", produto.estoque);
        }

        // Escreve no arquivo temporário, independentemente de ser alterado
        fprintf(temp, "%d,%s,%s,%s,%s,%.2f,%d\n", produto.id, produto.categoria, 
                produto.tipoAnimal, produto.marca, produto.descricao, 
                produto.preco, produto.estoque);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Produto com ID %d não encontrado.\n", id);
        remove(arqTemp);
    } else {
        remove(db_produtos);
        rename(arqTemp, db_produtos);
    }
}