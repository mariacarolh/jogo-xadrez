#include <stdio.h>
#include <stdlib.h> // Lib para limpar a tela

#define TAM_TABULEIRO 8 // Tamanho padrão do tabuleiro
#define MAGENTA "\x1b[35m" // Definindo a cor MAGENTA
#define RESET "\x1B[0m" // Reset de cor

// Peças pretas
const char pP = 'p'; // Peao
const char pT = 't'; // Torre
const char pC = 'c'; // Cavalo
const char pB = 'b'; // Bispo
const char pD = 'd'; // Dama
const char pR = 'r'; // Rei

const char eV = ' '; // Espaço vazio

// Peças brancas
const char bP = 'P'; // Peao
const char bT = 'T'; // Torre
const char bC = 'C'; // Cavalo
const char bB = 'B'; // Bispo
const char bD = 'D'; // Dama
const char bR = 'R'; // Rei

char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]; // Definir tamanho do tabuleiro 8 por 8

void limparTela()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirTabuleiro()
{
    limparTela();

    for (int i = 0; i < TAM_TABULEIRO; i++) // x
    {
        printf("  ---------------------------------\n");
        printf("%d ", 8 - i); // Inserir coordenada Y na coluna (1 à 8)

        for (int j = 0; j < TAM_TABULEIRO; j++) // y
        {
            char peca = tabuleiro[i][j];

            if(peca == pP || peca == pT || peca == pC || peca == pB || peca == pR || peca == pD)
            {
                printf("| " MAGENTA "%c " RESET, peca);
            }
            else
            {
                printf("| %c ", peca);
            }
        }
        printf("| \n");
    }
    printf("  ---------------------------------\n");
    printf("    a   b   c   d   e   f   g   h\n"); // Inserir coordenada X na coluna (A à H)
}

void iniciarTabuleiro()
{
    limparTela();
    // Array criado para posicionar as peças dentro do tabuleiro
    char posicoesIniciais[TAM_TABULEIRO][TAM_TABULEIRO] = 
    { 
        {pT, pC, pB, pD, pR, pB, pC, pT},
        {pP, pP, pP, pP, pP, pP, pP, pP},
        {eV, eV, eV, eV, eV, eV, eV, eV},
        {eV, eV, eV, eV, eV, eV, eV, eV},
        {eV, eV, eV, eV, eV, eV, eV, eV},
        {eV, eV, eV, eV, eV, eV, eV, eV},
        {bP, bP, bP, bP, bP, bP, bP, bP},
        {bT, bC, bB, bD, bR, bB, bC, bT}
    };

    for (int i = 0; i < TAM_TABULEIRO; i++)
    {
        for (int j = 0; j < TAM_TABULEIRO; j++)
        {
            // posicoesIniciais foi inserido ao exibirTabuleiro já com as peças em suas posições corretas
            tabuleiro[i][j] = posicoesIniciais[i][j];
        }
    }
}

int main()
{
    iniciarTabuleiro();
    exibirTabuleiro();
}