#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "agendamentos.h"
#include "clientes.h"

static char* db_agenda = "data/db_agenda.csv";
static char* db_clientes = "data/db_clientes.csv";
static char* arqTemp = "data/temp.csv";

// Implementação das funções do módulo agendamentos
bool buscarDonoByCPF(const char *cpf) {
    FILE *arquivo = fopen(db_clientes, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de donos.\n");
        return false;
    }

    char buffer[256];
    Cliente donoAtual;

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        // Lendo os dados do arquivo para a estrutura Dono
        sscanf(buffer, "%99[^,],%11[^,],%d", donoAtual.name, donoAtual.cpf, &donoAtual.idade);

        // Comparando o CPF buscado com o CPF atual
        if (strcmp(donoAtual.cpf, cpf) == 0) {
            fclose(arquivo);
            return true; // CPF encontrado
        }
    }

    fclose(arquivo);
    return false; // CPF não encontrado
}
static void cadastrarAgendamento() {
    Agendamento newAgendamento;

    printf("Nome do animal: ");
    setbuf(stdin, NULL);
    fgets(newAgendamento.nomeAnimal, sizeof(newAgendamento.nomeAnimal), stdin);
    newAgendamento.nomeAnimal[strcspn(newAgendamento.nomeAnimal, "\n")] = 0;

    printf("CPF do dono: ");
    setbuf(stdin, NULL);
    fgets(newAgendamento.cpfdono, sizeof(newAgendamento.cpfdono), stdin);
    newAgendamento.cpfdono[strcspn(newAgendamento.cpfdono, "\n")] = 0;

    if (!buscarDonoByCPF(newAgendamento.cpfdono)) {
        printf("CPF não cadastrado. Agendamento não pode ser realizado.\n");
        return;
    }

    printf("Serviço (ex: Banho, Tosa): ");
    setbuf(stdin, NULL);
    fgets(newAgendamento.servico, sizeof(newAgendamento.servico), stdin);
    newAgendamento.servico[strcspn(newAgendamento.servico, "\n")] = 0;

    printf("Data (dd/mm/yyyy): ");
    setbuf(stdin, NULL);
    fgets(newAgendamento.data, sizeof(newAgendamento.data), stdin);
    newAgendamento.data[strcspn(newAgendamento.data, "\n")] = 0;

    printf("Horário (hh:mm): ");
    setbuf(stdin, NULL);
    fgets(newAgendamento.horario, sizeof(newAgendamento.horario), stdin);
    newAgendamento.horario[strcspn(newAgendamento.horario, "\n")] = 0;

    FILE *arquivo = fopen(db_agenda, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos!\n");
        return;
    }

    fprintf(arquivo, "%s,%s,%s,%s,%s\n",
            newAgendamento.nomeAnimal,
            newAgendamento.cpfdono,
            newAgendamento.servico,
            newAgendamento.data,
            newAgendamento.horario);

    fclose(arquivo);
    printf("Agendamento registrado com sucesso!\n");
}


static void listarAgendamentos() {
    FILE *arquivo = fopen(db_agenda, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos!\n");
        return;
    }

    printf("--------------------------------------------------------------------\n");
    printf("| Nome do Animal | CPF do Dono   | Serviço  | Data       | Horário |\n");
    printf("--------------------------------------------------------------------\n");

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        Agendamento agendamento;
        sscanf(linha, "%99[^,],%14[^,],%49[^,],%10[^,],%5[^\n]",
               agendamento.nomeAnimal,
               agendamento.cpfdono,
               agendamento.servico,
               agendamento.data,
               agendamento.horario);

        printf("| %-14s | %-12s | %-8s | %-10s | %-7s |\n",
               agendamento.nomeAnimal,
               agendamento.cpfdono,
               agendamento.servico,
               agendamento.data,
               agendamento.horario);
    }

    printf("--------------------------------------------------------------------\n");
    fclose(arquivo);
}

static void buscarAgendamentoPorCPF() {
    char cpfBusca[15];
    printf("Digite o CPF do dono: ");
    setbuf(stdin, NULL);
    fgets(cpfBusca, sizeof(cpfBusca), stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = 0;

    FILE *arquivo = fopen(db_agenda, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos!\n");
        return;
    }

    printf("--------------------------------------------------------------------\n");
    printf("| Nome do Animal | CPF do Dono   | Serviço  | Data       | Horário |\n");
    printf("--------------------------------------------------------------------\n");

    char linha[256];
    bool encontrado = false;
    while (fgets(linha, sizeof(linha), arquivo)) {
        Agendamento agendamento;
        sscanf(linha, "%99[^,],%14[^,],%49[^,],%10[^,],%5[^\n]",
               agendamento.nomeAnimal,
               agendamento.cpfdono,
               agendamento.servico,
               agendamento.data,
               agendamento.horario);

        if (strcmp(agendamento.cpfdono, cpfBusca) == 0) {
            printf("| %-14s | %-12s | %-8s | %-10s | %-7s |\n",
                   agendamento.nomeAnimal,
                   agendamento.cpfdono,
                   agendamento.servico,
                   agendamento.data,
                   agendamento.horario);
            encontrado = true;
        }
    }

    if (!encontrado) {
        printf("Nenhum agendamento encontrado para o CPF '%s'.\n", cpfBusca);
    }

    printf("--------------------------------------------------------------------\n");
    fclose(arquivo);
}


void excluirAgendamento() {
    char cpfBusca[15];
    char dataBusca[11];
    bool encontrado = false;

    // Solicitando ao usuário os dados para buscar o agendamento
    printf("Digite o CPF do dono do animal: ");
    setbuf(stdin, NULL);
    fgets(cpfBusca, sizeof(cpfBusca), stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = 0;

    printf("Digite a data do agendamento (dd/mm/yyyy): ");
    setbuf(stdin, NULL);
    fgets(dataBusca, sizeof(dataBusca), stdin);
    dataBusca[strcspn(dataBusca, "\n")] = 0;

    // Abrindo o arquivo original para leitura
    FILE *arquivo = fopen(db_agenda, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de agendamentos!\n");
        return;
    }

    // Criando um arquivo temporário para salvar os dados atualizados
    FILE *arquivoTemp = fopen(arqTemp, "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao criar o arquivo temporário!\n");
        fclose(arquivo);
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Agendamento agendamentoAtual;

        // Lendo os dados do arquivo
        sscanf(
            linha,
            "%99[^,],%14[^,],%49[^,],%10[^,],%5[^\n]",
            agendamentoAtual.nomeAnimal,
            agendamentoAtual.cpfdono,
            agendamentoAtual.servico,
            agendamentoAtual.data,
            agendamentoAtual.horario
        );

        // Verificando se é o agendamento que deve ser excluído
        if (strcmp(agendamentoAtual.cpfdono, cpfBusca) == 0 &&
            strcmp(agendamentoAtual.data, dataBusca) == 0) {
            encontrado = true; // Marcar como encontrado
            printf("\nAgendamento de %s em %s foi excluído com sucesso!\n", 
                   agendamentoAtual.nomeAnimal, agendamentoAtual.data);
            continue; // Pular a gravação deste registro no arquivo temporário
        }

        // Salvando os registros que não serão excluídos
        fprintf(
            arquivoTemp,
            "%s,%s,%s,%s,%s\n",
            agendamentoAtual.nomeAnimal,
            agendamentoAtual.cpfdono,
            agendamentoAtual.servico,
            agendamentoAtual.data,
            agendamentoAtual.horario
        );
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    // Substituindo o arquivo original pelo temporário
    if (encontrado) {
        remove(db_agenda);
        rename(arqTemp, db_agenda);
    } else {
        printf("\nNenhum agendamento encontrado para o CPF '%s' na data '%s'.\n", cpfBusca, dataBusca);
        remove("data/temp_agendamentos.csv");
    }
}

//Por enquanto, será a função main
//quando terminarmos de implementar, será a função agenda()

void agenda(){
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while(1){
        printf("1 - Cadastrar Agendamento\n");
        printf("2 - Listar Agendamentos\n");
        printf("3 - Buscar agendamentos\n");
        printf("4 - Excluir Agendamento\n");
        printf("0 - Voltar\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                cadastrarAgendamento();
                break;
            case 2:
                listarAgendamentos();
                break;
            case 3:
                buscarAgendamentoPorCPF();
                break;
            case 4:
                excluirAgendamento();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente!\n");
                break;
        }
    }
    
}