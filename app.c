#include <stdio.h>
#define TAM_TABULEIRO 8 // Tamanho padrão do tabuleiro

// Peças pretas
const char pP = 'P'; // Peao
const char pT = 'T'; // Torre
const char pC = 'C'; // Cavalo
const char pB = 'B'; // Bispo
const char pD = 'D'; // Dama
const char pR = 'R'; // Rei

const char V = ' '; // Espaço vazio

// Peças brancas
const char bP = 'P'; // Peao
const char bT = 'T'; // Torre
const char bC = 'C'; // Cavalo
const char bB = 'B'; // Bispo
const char bD = 'D'; // Dama
const char bR = 'R'; // Rei

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