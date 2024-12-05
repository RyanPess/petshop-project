#ifndef AGENDAMENTOS_H
#define AGENDAMENTOS_H


//Estrutura de um agendamento
typedef struct {
    char nomeAnimal[100];
    char cpfdono[15];
    char servico[50]; // Exemplo: "Banho", "Tosa", etc.
    char data[11];    // Formato: "dd/mm/yyyy"
    char horario[6];  // Formato: "hh:mm"
} Agendamento;

//// Declaração das funções do módulo agendamentos

void agenda();


#endif//AGENDAMENTOS_H