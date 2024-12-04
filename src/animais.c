#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "animais.h"
#include "clientes.h"

static const char *db_animais = "data/db_animais.csv";
static const char *db_clientes = "data/db_clientes.csv";
static const char *arqTemp = "data/temp.csv"; //Para fazer alterações no arquivo é necessário um arquivo temporário


int totalAnimais = 0;
static void calcularTotalAnimais(){
    FILE *arquivo = fopen(db_animais, "r");
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)!= NULL) {
        if (strlen(linha) > 1)
            totalAnimais++;
    }
    fclose(arquivo);
}

static void salvarAnimal(Animal animal) {

    FILE *arquivo = fopen(db_animais, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(
        arquivo, 
        "%s,%s,%s,%s,%.2f\n", 
        animal.nome,
        animal.especie,
        animal.raca,
        animal.cpfdono,
        animal.peso
    );

    fclose(arquivo);

    printf("\nAnimal cadastrado com sucesso!\n");
}
static bool buscarDonoByCPF(char* cpf){
    
    Cliente dono;
    
    bool encontrado = false;
    FILE *arquivo = fopen(db_clientes, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return false;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo)!= NULL) {
        sscanf(buffer, "%99[^,],%11[^,],%d", dono.name, dono.cpf, &dono.idade);
        
        if (strcmp(dono.cpf, cpf) == 0) {
            encontrado = true;
            break;
        }
    }
    fclose(arquivo);
    if (!encontrado) {
        printf("\n'%s' CPF não cadastrado.\n", cpf);
    }
    return encontrado;
}
static void cadastrarAnimal(){
    if (totalAnimais >= MAX_ANIMAIS) {
        printf("Limite de animais atingido!\n");
        return;
    }

    Animal newAnimal;

    // Nome do animal
    printf("Qual o nome do animal: ");
    setbuf(stdin, NULL);
    fgets(newAnimal.nome, 100, stdin);
    newAnimal.nome[strcspn(newAnimal.nome, "\n")] = 0;  // Remove o \n

    // Espécie do animal
    printf("Qual a espécie do animal: ");
    setbuf(stdin, NULL);
    fgets(newAnimal.especie, 50, stdin);
    newAnimal.especie[strcspn(newAnimal.especie, "\n")] = 0;

    // Raça do animal
    printf("Qual a raça do animal: ");
    setbuf(stdin, NULL);
    fgets(newAnimal.raca, 50, stdin);
    newAnimal.raca[strcspn(newAnimal.raca, "\n")] = 0;

    // Peso do animal
    printf("Digite o peso do animal: ");
    while (scanf("%f", &newAnimal.peso) != 1 || newAnimal.peso <= 0) {
        printf("Quantidade inválida. Digite novamente: ");
        setbuf(stdin, NULL);
    }

    if (strlen(newAnimal.nome) == 0 || strlen(newAnimal.especie) == 0 || strlen(newAnimal.raca) == 0) {
        printf("Erro: Todos os campos devem ser preenchidos!\n");
        return;
    }

    // CPF do dono
    printf("Digite o CPF do dono(cadastrado): ");
    setbuf(stdin, NULL);
    fgets(newAnimal.cpfdono, 15, stdin);
    newAnimal.cpfdono[strcspn(newAnimal.cpfdono, "\n")] = 0;
    
    // Verificando se o CPF do dono está cadastrado
    if(buscarDonoByCPF(newAnimal.cpfdono)){
        salvarAnimal(newAnimal);
        printf("\nAnimal salvo com sucesso!\n");
    }else {
        printf("Cadastro do animal não concluído. CPF do dono não encontrado.\n");
    }
}

static void buscarAnimalByCPF(){
    //Implementar a função para buscar animal por CPF
}
static void listarAnimais(){
    //Implementar a função para listar animais
}

static void editarAnimais(){
    //Implementar a função para editar animais cadastrados
}


//Por enquanto, será a função main
//quando terminarmos de implementar, será a função gerenciamentoAnimais()

void gerenciamentoAnimais(){
    int opcao;
    totalAnimais = 0;
    calcularTotalAnimais();
    while(1){
        printf("\n1 - Cadastrar Animal");
        printf("\n2 - Listar Animais");
        printf("\n3 - Buscar animal por CPF");
        printf("\n4 - Editar Animais");
        printf("\n0 - Voltar");
        printf("\n\nDigite a opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                cadastrarAnimal();
                break;
            case 2:
                listarAnimais();
                break;
            case 3:
                buscarAnimalByCPF();
                break;
            case 4:
                editarAnimais();
                break;
            case 0:
                return;
            default:
                printf("\nOpção inválida. Tente novamente!\n");
                break;
        }
    }
    
        
}