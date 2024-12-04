#ifndef ANIMAIS_H
#define ANIMAIS_H

// Define o número máximo de animais
#define MAX_ANIMAIS 200

//Estrutura do animal
typedef struct {
    char nome[100];
    char especie[50];
    char raca[50];
    float peso;
    char cpfdono[15];
} Animal;

// Declaração das funções do módulo saudacao

void gerenciamentoAnimais();



#endif// ANIMAIS_H