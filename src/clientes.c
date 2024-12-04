#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "clientes.h"
//Constante, diretório do banco de dados dos clientes
static const char *db_clientes = "data/db_clientes.csv";

// Implementação das funções do módulo clientes
static void salvarCliente(Cliente cliente);
static void cadastrarCliente();
static void listarClientes();
static void editarCliente();


//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoClientes()

void gerenciamentoClientes(){
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
    } 

}

static void salvarCliente(Cliente cliente){
    FILE *arquivo = fopen(db_clientes, "a");
    if(arquivo==NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "%s,%s,%d,%s\n", cliente.name, cliente.cpf, cliente.idade, cliente.endereco);
    fclose(arquivo);

    printf("\nCliente cadastrado com sucesso!\n");
}
static void cadastrarCliente(){
    Cliente newCliente;
    printf("Por favor, informe o nome do cliente:");
    setbuf(stdin,NULL);
    fgets(newCliente.name,100,stdin);
    newCliente.name[strcspn(newCliente.name, "\n")] = 0; // remove o \n da string
    
    printf("Informe o CPF do cliente: ");
    setbuf(stdin,NULL);
    fgets(newCliente.cpf,12,stdin);
    newCliente.cpf[strcspn(newCliente.cpf, "\n")] = 0;

    //Adicionei algumas regras básicas
    printf("Informe a idade do cliente: ");
    scanf("%d",&newCliente.idade);
    if(newCliente.idade < 18){
        printf("\nIdade inválida! O cliente deve ser maior de 18 anos.\n");
        return;
    }
    printf("Informe o endereco do cliente: ");
    setbuf(stdin,NULL);
    fgets(newCliente.endereco,100,stdin);
    newCliente.endereco[strcspn(newCliente.endereco, "\n")] = 0;

    if(strlen(newCliente.name) <= 1 || strlen(newCliente.cpf) <= 1){
        printf("\nTodos os campos devem ser preenchidos com dados corretos!\n");
        return;
    }
    
    salvarCliente(newCliente);
}

static void listarClientes(){

    Cliente cliente;
   
    FILE *arquivo = fopen(db_clientes, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo! Verifique se ele existe e tente novamente.\n");
        return;
    }

    printf("\nLista de Clientes Cadastrados:\n");
    printf("----------------------------------------------\n");
    printf("| Nome                   | CPF       | Idade |\n");
    printf("----------------------------------------------\n");

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) !=NULL) { 
        // Divide a linha nos campos nome, cpf e idade usando sscanf
        if (sscanf(linha, "%99[^,],%11[^,],%d", 
        cliente.name,
        cliente.cpf,
        &cliente.idade) == 3) {
            // Exibe os dados do cliente
            printf("| %-22s | %-9s | %5d |\n",
            cliente.name,
            cliente.cpf,
            cliente.idade);
        }
    }
    printf("---------------------------------------\n");
    fclose(arquivo);
}

static void editarCliente(){
    printf("Informe o CPF do cliente para editar:");
}
