#include <stdio.h>
#define TAM_TABULEIRO 8 // Tamanho padrão do tabuleiro

char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]; // Definir tamanho do tabuleiro 8 por 8

void exibirTabuleiro()
{
    for (int i = 1; i <= TAM_TABULEIRO; i++)
    {
        printf("  ---------------------------------\n"); 
        printf("%d", 9 - i); // Inserir coordenada Y na coluna (1 à 8)

        for (int j = 1; j <= TAM_TABULEIRO; j++)
        {
            printf("|   ");
        }
        printf("| \n");
        
    }
    printf("  ---------------------------------\n");
    printf("    a   b   c   d   e   f   g   h\n"); // Inserir coordenada X na coluna (A à H)
}

int main()
{
    exibirTabuleiro();
}