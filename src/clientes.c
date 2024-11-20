#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "clientes.h"


// Implementação das funções do módulo clientes

static cadastrarCliente(){

}

static void listarClientes(){

}

static void editarCliente(){

}

//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoCLientes()

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    int opcao;
    while (1){
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Listar Clientes\n");
        printf("3 - Editar Cliente\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                editarCliente(); 
                break;
            case 0:
                return;
                break;
            default:
                printf("Opção inválida. Tente novamente!\n");
                break;
        }
    } ;

    return 0;
}