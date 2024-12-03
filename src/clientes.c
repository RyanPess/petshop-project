#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include "clientes.h"
//Constante, diretório do banco de dados dos clientes
const char *db_clientes = "data/db_clientes.csv";

// Implementação das funções do módulo clientes
static void salvarCliente(Cliente cliente);
static void cadastrarCliente();
static void listarClientes();
static void editarCliente();
void normalizarCpf(char *cpf);



//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoClientes()

void gerenciamentoClientes(){
    setlocale(LC_ALL, "pt_BR.UTF8");
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

    fprintf(arquivo, "%s, %s, %d\n", cliente.name, cliente.cpf, cliente.idade);
    fclose(arquivo);

    printf("\nCliente cadastrado com sucesso!\n");
}
static void cadastrarCliente(){
    Cliente newCliente;
    printf("Por favor, informe o nome do cliente:");
    setbuf(stdin,NULL);
    fgets(newCliente.name,100,stdin);
    newCliente.name[strcspn(newCliente.name, "\n")] = 0; // remove o \n da string
    
    printf("Informe o CPF do cliente:");
   // setbuf(stdin,NULL);
    fgets(newCliente.cpf,11,stdin);
    newCliente.cpf[strcspn(newCliente.cpf, "\n")] = 0;
    //Adicionei algumas regras básicas
    printf("Qual a idade do cliente? ");
    while (getchar() != '\n');
    scanf("%d",&newCliente.idade);
    if(newCliente.idade < 18){
        printf("\nIdade inválida! O cliente deve ser maior de 18 anos.\n");
        return;
    }

    if(strlen(newCliente.name) <= 1 || strlen(newCliente.cpf) <= 1){
        printf("\nTodos os campos devem ser preenchidos com dados corretos!\n");
        return;
    }
    
    salvarCliente(newCliente);
}

static void listarClientes(){
   
    FILE *arquivo = fopen(db_clientes, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo! Verifique se ele existe e tente novamente.\n");
        return;
    }

    printf("\nLista de Clientes Cadastrados:\n");
    printf("---------------------------------------\n");
    printf("| Nome                   | CPF       | Idade |\n");
    printf("---------------------------------------\n");

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) !=NULL) { 
        char nome[100], cpf[12];
        int idade;

        // Divide a linha nos campos nome, cpf e idade usando sscanf
        if (sscanf(linha, "%99[^,],%11[^,],%d", nome, cpf, &idade) == 3) {
            printf("| %-22s | %-9s | %5d |\n", nome, cpf, idade);
        }
    

    printf("---------------------------------------\n");
    }
    fclose(arquivo);
}


static void editarCliente() {
    char cpfBusca[12];
    printf("Informe o CPF do cliente para editar: ");
    setbuf(stdin, NULL);
    fgets(cpfBusca, sizeof(cpfBusca), stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = 0; // Remove o '\n'
    normalizarCpf(cpfBusca); // Normaliza o CPF

    FILE *arquivo = fopen(db_clientes, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo! Verifique se ele existe e tente novamente.\n");
        return;
    }

    Cliente clientes[100];
    int totalClientes = 0;
    bool clienteEncontrado = false;

    // Ler os clientes do arquivo
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Cliente cliente;
        linha[strcspn(linha, "\n")] = 0; // Remove o '\n' da linha
        if (sscanf(linha, "%99[^,],%11[^,],%d", cliente.name, cliente.cpf, &cliente.idade) == 3) {
            normalizarCpf(cliente.cpf); // Normaliza o CPF do cliente
            clientes[totalClientes++] = cliente;
            if (strcmp(cliente.cpf, cpfBusca) == 0) {
                clienteEncontrado = true;
            }
        }
    }
    fclose(arquivo);

    if (!clienteEncontrado) {
        printf("Cliente com CPF %s não encontrado.\n", cpfBusca);
        return;
    }

    // Editar o cliente
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].cpf, cpfBusca) == 0) {
            printf("Cliente encontrado:\n");
            printf("Nome: %s, CPF: %s, Idade: %d\n", clientes[i].name, clientes[i].cpf, clientes[i].idade);

            printf("Informe o novo nome (ou pressione ENTER para manter): ");
            setbuf(stdin, NULL);
            char novoNome[100];
            fgets(novoNome, sizeof(novoNome), stdin);
            novoNome[strcspn(novoNome, "\n")] = 0;

            if (strlen(novoNome) > 0) {
                strcpy(clientes[i].name, novoNome);
            }

            printf("Informe o novo CPF (ou pressione ENTER para manter): ");
            char novoCpf[12];
            fgets(novoCpf, sizeof(novoCpf), stdin);
            novoCpf[strcspn(novoCpf, "\n")] = 0;

            if (strlen(novoCpf) > 0) {
                normalizarCpf(novoCpf);
                strcpy(clientes[i].cpf, novoCpf);
            }

            printf("Informe a nova idade (ou 0 para manter): ");
            int novaIdade;
            scanf("%d", &novaIdade);
            if (novaIdade > 0) {
                clientes[i].idade = novaIdade;
            }

            printf("Cliente atualizado com sucesso!\n");
            break;
        }
    }

    // Reescrever o arquivo com os dados atualizados
    arquivo = fopen(db_clientes, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < totalClientes; i++) {
        fprintf(arquivo, "%s,%s,%d\n", clientes[i].name, clientes[i].cpf, clientes[i].idade);
    }
    fclose(arquivo);

    printf("Dados do arquivo atualizados com sucesso!\n");
}
void normalizarCpf(char *cpf) {
    char temp[12] = {0};
    int j = 0;
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            temp[j++] = cpf[i];
        }
    }
    strcpy(cpf, temp);
}