#ifndef PRODUTOS_H
#define PRODUTOS_H

#define MAX_PRODUTOS 200

// Estrutura do produto

typedef struct {
    int id;       // C�digo do produto
    char categoria[50];   // Ex: Alimento, Higiene
    char tipoAnimal[30];  // Ex: C�es, Gatos
    char marca[50];       // Ex: Royal Canin, Whiskas
    char descricao[100];  // Ex: Ra��o premium
    float preco;          // Pre�o do produto
    int estoque;          // Quantidade em estoque
} Produto;

void gerenciamentoProdutos();

#endif//PRODUTOS_H