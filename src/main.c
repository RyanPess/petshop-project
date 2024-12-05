#include <stdio.h>
#include <stdlib.h>

//Modulos implementados
#include "clientes.h"
#include "produtos.h"
#include "animais.h"
#include "agendamentos.h"
//#include "relatorios.h"

char* arqTemp = "data/temp.csv";
static void gerarArquivoTemp();

int main() {

    int opcao;

    while(1){
        gerarArquivoTemp();
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
                printf("::::::::::: Gerenciamento cliente ::::::::::\n\n");
                gerenciamentoClientes();
                break;
            case 2:
                printf("::::::::::: Gerenciamento animal ::::::::::\n\n");
                gerenciamentoAnimais();
                break;
            case 3:
                printf("::::::::::: Gerenciamento produtos::::::::::\n\n");
                gerenciamentoProdutos();
                break;
            case 4:
                printf("::::::::::: Agendamento ::::::::::\n\n");
                agenda();
                break;
            case 5:
                printf("::::::::::: Relatório financeiro ::::::::::\n\n");
                //relatorioFinanceiro();
                break;
            case 0:
                printf("Programa encerrado.\n");
                return 0;
            default:
                printf("\n Opcao invalida. Tente novamente!");
                break;
        }
    }

    return 0;
}

static void gerarArquivoTemp(){
    FILE *arq;
    arq = fopen(arqTemp, "w");
    fclose(arq);
}