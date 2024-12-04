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

static void buscarAnimalByCPF() {
    Animal animal;
    char cpfbusca[12]; // CPF do dono a ser buscado
    bool encontrado = false;

    printf("Digite o CPF do dono(cadastrado): ");
    setbuf(stdin, NULL);
    fgets(cpfbusca, sizeof(cpfbusca), stdin);
    cpfbusca[strcspn(cpfbusca, "\n")] = 0; // Remove o '\n'

    FILE *arquivo = fopen(db_animais, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de animais!\n");
        return;
    }

    printf("\nAnimais encontrados para o CPF '%s':\n", cpfbusca);
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| Nome                | Especie       | Raca              | CPF do dono            | Peso   |\n");
    printf("---------------------------------------------------------------------------------------------\n");

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        sscanf(buffer, "%99[^,],%99[^,],%99[^,],%11[^,],%f",
               animal.nome,
               animal.especie,
               animal.raca,
               animal.cpfdono,
               &animal.peso);

        if (strcmp(animal.cpfdono, cpfbusca) == 0) {
            encontrado = true;
            printf("| %-20s | %-16s | %-18s | %-20s | %7.2f |\n", 
                    animal.nome,
                    animal.especie,
                    animal.raca,
                    animal.cpfdono,
                    animal.peso);
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Nenhum animal encontrado para o CPF informado.\n");
    }
}

static void listarAnimais() {
    Animal animal;

    FILE *arquivo = fopen(db_animais, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de animais!\n");
        return;
    }

    printf("---------------------------------------------------------------------------------------------\n");
    printf("| Nome                | Especie       | Raca              | CPF do dono            | Peso   |\n");
    printf("---------------------------------------------------------------------------------------------\n");

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        sscanf(buffer, "%99[^,],%99[^,],%99[^,],%11[^,],%f",
               animal.nome,
               animal.especie,
               animal.raca,
               animal.cpfdono,
               &animal.peso);

        printf("| %-20s | %-16s | %-18s | %-20s | %7.2f |\n", 
                animal.nome,
                animal.especie,
                animal.raca,
                animal.cpfdono,
                animal.peso);
    }

    fclose(arquivo);
}

static void lerString(char *buffer, size_t tamanho, const char *mensagem) {
    printf("%s", mensagem);
    setbuf(stdin, NULL);
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove o '\n'
}

static void editarAnimais() {
    char nomeBusca[100];
    bool encontrado = false;

    printf("Digite o nome do animal que deseja editar: ");
    setbuf(stdin, NULL);
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    FILE *arquivo = fopen(db_animais, "r");
    FILE *temp = fopen(arqTemp, "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        return;
    }

    Animal animal;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        sscanf(buffer, "%99[^,],%99[^,],%99[^,],%11[^,],%f",
               animal.nome,
               animal.especie,
               animal.raca,
               animal.cpfdono,
               &animal.peso);

        if (strcmp(animal.nome, nomeBusca) == 0) {
            encontrado = true;

            printf("Novo nome do animal: ");
            lerString(animal.nome, sizeof(animal.nome), "");

            printf("Nova espécie: ");
            lerString(animal.especie, sizeof(animal.especie), "");

            printf("Nova raça: ");
            lerString(animal.raca, sizeof(animal.raca), "");

            printf("Novo peso: ");
            while (scanf("%f", &animal.peso) != 1 || animal.peso <= 0) {
                printf("Peso inválido. Digite novamente: ");
                setbuf(stdin, NULL);
            }
        }

        fprintf(temp, "%s,%s,%s,%s,%.2f\n", 
                animal.nome, 
                animal.especie, 
                animal.raca, 
                animal.cpfdono, 
                animal.peso);
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado) {
        remove(db_animais);
        rename(arqTemp, db_animais);
        printf("Animal editado com sucesso!\n");
    } else {
        remove(arqTemp);
        printf("Animal não encontrado.\n");
    }
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