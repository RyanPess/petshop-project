#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 200

// Estrutura do cliente
typedef struct{
    char name[100];
    char cpf[11];
    int idade;
    int numCadastro; //cada cliente terá um número de cadastro único
} Cliente;

// Declaração das funções do módulo clientes

void gerenciamentoClientes();  

#endif // CLIENTES_H