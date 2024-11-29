#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "relatorios.h"

static void relatorioProdutos(){
    // Implementação do relatório de produtos
}

static void relatorioClientes(){
    // Implementação do relatório de clientes
}

void relatorioFinanceiro(){
    // Inicializa o locale para suportar caracteres acentuados
    setlocale(LC_ALL, "Portuguese");
    
    int opcao;
    
    while(1){
        printf("1 - Relatório de Produtos\n");
        printf("2 - Relatório de Clientes\n");
        printf("0 - Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                relatorioProdutos();
                break;
            case 2:
                relatorioClientes();
                break;
            case 3:
                return;
            default:
                printf("Opção inválida!\n");
        }
    }
    
   // return 0;
}
