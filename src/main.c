#include <stdio.h>
#include <stdlib.h>

//Modulos implementados
#include "clientes.h"
#include "produtos.h"
#include "animais.h"
#include "agendamentos.h"
#include "relatorios.h"

int main() {

    int opcao;

    while(1){
        system("cls");
        printf("::::::::::: MENU PETSHOP ::::::::::\n\n");
        printf("1 - Gerenciamento de Clientes\n");
        printf("2 - Gerenciamento de Animais\n");
        printf("3 - Gerenciamento de Produtos\n");
        printf("4 - Agendamento\n");
        printf("5 - Relatório financeiro\n");
        printf("0 - Encerrar programa\n");

        printf("\n\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                system("cls");
                printf("::::::::::: Gerenciamento cliente ::::::::::\n\n");
                gerenciamentoClientes();
                break;
            case 2:
                system("cls");
                printf("::::::::::: Gerenciamento animal ::::::::::\n\n");
                gerenciamentoAnimais();
                break;
            case 3:
                system("cls");
                printf("::::::::::: Gerenciamento produtos::::::::::\n\n");
                gerenciamentoProdutos();
                break;
            case 4:
                system("cls");
                printf("::::::::::: Agendamento ::::::::::\n\n");
                agenda();
                break;
            case 5:
                system("cls");
                printf("::::::::::: Relatório financeiro ::::::::::\n\n");
                relatorioFinanceiro();
                break;
            case 0:
                system("cls");
                printf("Programa encerrado.\n");
                return 0;
            default:
                system("cls");
                printf("\n Opcao invalida. Tente novamente!");
                break;
        }
    }

    return 0;
}
