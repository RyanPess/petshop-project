#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "produtos.h"

// Implementação das funções do módulo produtos

void cadastrarProduto(){
    // Implementar a função para cadastrar um novo produto
}

void listarProdutos(){
    // Implementar a função para listar todos os produtos cadastrados
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