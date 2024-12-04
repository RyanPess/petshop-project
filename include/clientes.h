#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 200

// Estrutura do cliente
typedef struct{
    char name[50];
    char cpf[12];
    int idade;
    char endereco[100];
} Cliente;

// Declaração das funções do módulo clientes

void gerenciamentoClientes();  

#endif // CLIENTES_H