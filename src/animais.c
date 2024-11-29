#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "animais.h"

static void cadastrarAnimal(){
    //Implementar a função para cadastrar um novo animal
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
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    while(1){
        printf("\n1 - Cadastrar Animal");
        printf("\n2 - Listar Animais");
        printf("\n3 - Editar Animais");
        printf("\n4 - Voltar");
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
                editarAnimais();
                break;
            case 4:
                return;
            default:
                printf("\nOpção inválida. Tente novamente!\n");
                break;
        }
    }
    
//    return 0;
        
}