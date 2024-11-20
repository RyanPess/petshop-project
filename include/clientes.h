#ifndef CLIENTES_H
#define CLIENTES_H

#define MAX_CLIENTES 200

// Estrutura do cliente
typedef struct{
    char name[50];
} Cliente;

// Declaração das funções do módulo clientes

void cadastrarCliente();
void listarClientes();

#endif // CLIENTES_H