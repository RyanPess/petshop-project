#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "clientes.h"
//#include "petshop-project/include/clientes.h"
//VERIFICAR UMA FORMA DE IMPLEMENTAR A BIBLIOTECA CLIENTE.H

// Implementação das funções do módulo clientes
static void salvarCliente(Cliente cliente);
static void cadastrarCliente();
static void listarClientes();
//COMO ARMAZENAR OS DADOS DE CADA CLIENTE??? CRIAR UM VETOR PARA CADA ATRIBUTO DA STRUCT?
static void editarCliente();


//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoClientes()

void gerenciamentoClientes(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    int opcao;
    printf("\n::::BEM VINDO A ÁREA DE GERENCIAMENTO DE CLIENTES:::::\n POR FAVOR, ESCOLHA UMA DAS OPÇÕES\n");
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
    } 

    //return 0;
}

static void salvarCliente(Cliente cliente){
    FILE *arquivo = fopen("", "a");
    if(arquivo==NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%s, %s, %d\n", cliente.name, cliente.cpf, cliente.idade);
    fclose(arquivo);

    printf("\nCliente cadastrado com sucesso!");
}
static void cadastrarCliente(){
    Cliente newCliente;
    printf("Por favor, informe o nome do cliente:");
    setbuf(stdin,NULL);
    fgets(newCliente.name,100,stdin);
    newCliente.name[strcspn(newCliente.name, "\n")] = 0; // remove o \n da string
    
    printf("Informe o CPF do cliente:");
    setbuf(stdin,NULL);
    fgets(newCliente.cpf,11,stdin);
    newCliente.cpf[strcspn(newCliente.cpf, "\n")] = 0;

    //Adicionei algumas regras básicas
    printf("Qual a idade do cliente? ");
    scanf("%d",&newCliente.idade);
    if(newCliente.idade < 18){
        printf("Idade inválida! O cliente deve ser maior de 18 anos.\n");
        return;
    }

    if(strlen(newCliente.name) <= 1 || strlen(newCliente.cpf) <= 1){
        printf("Todos os campos devem ser preenchidos com dados corretos!\n");
        return;
    }
    
    salvarCliente(newCliente);
}

static void listarClientes(){
    printf("\nTodos clientes cadastrados no petshop\n");
}

static void editarCliente(){
    printf("Informe o CPF do cliente para editar:");
}
