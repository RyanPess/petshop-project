#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 200

// Estrutura do cliente
typedef struct{
    char nome[50];
    char cpf[11];
    int idade;
    int codCliente;
} Cliente;

// Declaração das funções do módulo clientes

void gerenciamentoClientes();

#endif // CLIENTES_H