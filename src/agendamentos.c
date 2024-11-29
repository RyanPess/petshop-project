#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "agendamentos.h"

// Implementação das funções do módulo agendamentos

static void cadastrarAgendamento(){
    // Implementar a função para cadastrar um novo agendamento
}

static void listarAgendamentos(){
    // Implementar a função para listar todos os agendamentos
}

static void excluirAgendamento(){
    // Implementar a função para excluir um agendamento
}

static void alterarAgendamento(){
    // Implementar a função para alterar um agendamento
}

//Por enquanto, será a função main
//quando terminarmos de implementar, será a função agenda()

void agenda(){
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    while(1){
        printf("1 - Cadastrar Agendamento\n");
        printf("2 - Listar Agendamentos\n");
        printf("3 - Excluir Agendamento\n");
        printf("4 - Alterar Agendamento\n");
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
                excluirAgendamento();
                break;
            case 4:
                alterarAgendamento();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente!\n");
                break;
        }
    }
    
    //return 0;
}