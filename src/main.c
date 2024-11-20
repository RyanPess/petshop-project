#include <stdio.h>
#include "clientes.h"  // Inclui o módulo calculadora
#include "animais.h"

int main() {
    //Definimos a quantidade de clientes e animais que o sistema suporta
    Cliente clientes[MAX_CLIENTES];  
    Animal animais[MAX_ANIMAIS];

    int opcao;

    while(1){
        printf("::::::::::: MENU PETSHOP ::::::::::\n\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Animal\n");
        printf("3 - Listar Clientes\n");
        printf("4 - Listar Animais\n");
        printf("5 - Listar produtos / servicos\n");
        printf("6 - Agendamento\n");
        printf("7 - Relatório financeiro\n");
        printf("0 - Encerrar programa\n");

        printf("\n\nEscolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                printf("::::::::::: Cadastro cliente ::::::::::\n\n");
                //cadastrarCliente();
                break;
            case 2:
                printf("::::::::::: Cadastro animal ::::::::::\n\n");
                //cadastrarAnimal();
                break;
            case 3:
                printf("::::::::::: Listar clientes ::::::::::\n\n");
                //listarClientes();
                break;
            case 4:
                printf("::::::::::: Listar animais ::::::::::\n\n");
                //listarAnimais();
                break;
            case 5:
                printf("::::::::::: Listar produtos / servicos ::::::::::\n\n");
                //listarProdutosServicos();
                break;
            case 6:
                printf("::::::::::: Agendamento ::::::::::\n\n");
                //agenda();
                break;
            case 7:
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
