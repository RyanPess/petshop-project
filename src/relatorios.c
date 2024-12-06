#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#include "relatorios.h"

typedef struct {
    char categoria[50];
    char tipoAnimal[30];
    char marca[50];
    char descricao[100];
    float preco;
    int estoque;
} Produto;

void relatorioFinanceiro(){
    
    Produto produtos[] = {
        {"Alimento", "Pássaros", "Kaytee", "Alimento para pássaros", 60.00, 50},
        {"Alimento", "Pássaros", "Zupreem", "Alimento para pássaros", 75.00, 40},
        {"Alimento", "Pássaros", "Harrison's", "Alimento para pássaros", 90.00, 30},
        {"Alimento", "Gatos", "Whiskas", "Ração básica", 75.00, 100},
        {"Alimento", "Gatos", "Friskies", "Ração para adultos", 85.00, 70},
        {"Alimento", "Gatos", "Kibbles 'n Bits", "Ração para gatos", 100.00, 60},
        {"Alimento", "Gatos", "Orijen", "Ração premium", 150.00, 25},
        {"Alimento", "Gatos", "Acana", "Ração natural", 145.00, 30},
        {"Higiene", "Gatos", "Frontline", "Antipulgas", 90.00, 25},
        {"Higiene", "Gatos", "Advantix", "Antipulgas", 95.00, 20},
        {"Higiene", "Gatos", "Hartz", "Antipulgas", 85.00, 35},
        {"Higiene", "Gatos", "Oster", "Escovas", 25.00, 60},
        {"Alimento", "Cães", "Royal Canin", "Ração premium", 120.50, 50},
        {"Alimento", "Cães", "Hill's Science", "Ração científica", 140.00, 30},
        {"Alimento", "Cães", "Purina", "Ração básica", 90.00, 100},
        {"Alimento", "Cães", "Pedigree", "Ração para adultos", 85.00, 80},
        {"Alimento", "Cães", "Nutro", "Ração natural", 130.00, 20},
        {"Higiene", "Cães", "Frontline", "Antipulgas", 100.00, 20},
        {"Higiene", "Cães", "Advantix", "Antipulgas", 110.00, 15},
        {"Higiene", "Cães", "Earthbath", "Xampu", 55.00, 50},
        {"Higiene", "Cães", "Oster", "Escovas", 30.00, 70},
        {"Medicamento", "Cães", "Pfizer", "Vacinas", 200.00, 10},
        {"Medicamento", "Cães", "Merck", "Vacinas", 210.00, 12},
        {"Medicamento", "Cães", "Zoetis", "Vacinas", 180.00, 15},
        {"Medicamento", "Cães", "Bayer", "Medicamentos gerais", 150.00, 20},
        {"Acessório", "Cães", "PetSafe", "Coleiras", 50.00, 80},
        {"Acessório", "Cães", "Kong", "Brinquedos", 45.00, 100},
        {"Acessório", "Cães", "Chuckit!", "Brinquedos", 60.00, 90},
        {"Acessório", "Cães", "Armarkat", "Camas", 200.00, 25}
    };

    float valor_totalP = 0, valor_totalG = 0, valor_totalC = 0;
    short opcao;
    int tamanho = sizeof(produtos) / sizeof(produtos[0]);

    while(1){
        printf("Selecione uma opção:\n");
        printf("1 - Valor Bruto de vendas de produtos para Pássaros\n");
        printf("2 - Valor Bruto de produtos para vendas de Gatos\n");
        printf("3 - Valor Bruto de produtos para vendas de Cães\n");
        printf("0 - Voltar\n");
        scanf("%hd", &opcao);

        switch (opcao) {
            case 1:
                for (int i = 0; i < tamanho; i++) {
                    if (strcmp(produtos[i].tipoAnimal, "Pássaros") == 0) {
                        valor_totalP += produtos[i].preco * produtos[i].estoque;
                    }
                }
                printf("O valor bruto de produtos para Pássaros: %.2f\n", valor_totalP);
                break;
            case 2:
                for (int i = 0; i < tamanho; i++) {
                    if (strcmp(produtos[i].tipoAnimal, "Gatos") == 0) {
                        valor_totalG += produtos[i].preco * produtos[i].estoque;
                    }
                }
                printf("O valor bruto de produtos para Gatos: %.2f\n", valor_totalG);
                break;
            case 3:
                for (int i = 0; i < tamanho; i++) {
                    if (strcmp(produtos[i].tipoAnimal, "Cães") == 0) {
                        valor_totalC += produtos[i].preco * produtos[i].estoque;
                    }
                }
                printf("O valor bruto de produtos para Cães: %.2f\n", valor_totalC);
                break;
            case 0:
                printf("Saindo...\n");
                return ;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}
