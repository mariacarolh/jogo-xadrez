#include <stdio.h>
#include <stdlib.h> // Lib para limpar a tela

#define TAM_TABULEIRO 8          // Tamanho padrão do tabuleiro
#define MAGENTA "\x1b[38;5;200m" // Definindo a cor MAGENTA
#define RESET "\x1B[0m"          // Reset de cor

// Peças pretas
const char peaoPreto = 'p';   // Peao
const char torrePreta = 't';  // Torre
const char cavaloPreto = 'c'; // Cavalo
const char bispoPreto = 'b';  // Bispo
const char damaPreta = 'd';   // Dama
const char reiPreto = 'r';    // Rei

const char espacoVazio = ' '; // Espaço vazio

// Peças brancas
const char peaoBranco = 'P';   // Peao
const char torreBranca = 'T';  // Torre
const char cavaloBranco = 'C'; // Cavalo
const char bispoBranco = 'B';  // Bispo
const char damaBranca = 'D';   // Dama
const char reiBranco = 'R';    // Rei

int turno = 0; // Variável para turnos (0 brancas e 1 pretas)

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

    for (int x = 0; x < TAM_TABULEIRO; x++) // x
    {
        printf("   ---------------------------------\n");
        printf(" %d ", 8 - x); // Inserir coordenada Y na coluna (1 à 8)

        for (int y = 0; y < TAM_TABULEIRO; y++) // y
        {
            char peca = tabuleiro[x][y];

            if (peca == peaoPreto || peca == torrePreta || peca == cavaloPreto || peca == bispoPreto || peca == reiPreto || peca == damaPreta)
            {
                printf("| " MAGENTA "%c" RESET " ", tabuleiro[x][y]);
            }
            else
            {
                printf("| %c ", peca);
            }
        }
        printf("| \n");
    }
    printf("   ---------------------------------\n");
    printf("     a   b   c   d   e   f   g   h\n"); // Inserir coordenada X na coluna (A à H)
}

void iniciarTabuleiro()
{
    limparTela();
    // Array criado para posicionar as peças dentro do tabuleiro
    char posicoesIniciais[TAM_TABULEIRO][TAM_TABULEIRO] =
        {
            {torrePreta, cavaloPreto, bispoPreto, damaPreta, reiPreto, bispoPreto, cavaloPreto, torrePreta},
            {peaoPreto, peaoPreto, peaoPreto, peaoPreto, peaoPreto, peaoPreto, peaoPreto, peaoPreto},
            {espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio},
            {espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio},
            {espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio},
            {espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio, espacoVazio},
            {peaoBranco, peaoBranco, peaoBranco, peaoBranco, peaoBranco, peaoBranco, peaoBranco, peaoBranco},
            {torreBranca, cavaloBranco, bispoBranco, damaBranca, reiBranco, bispoBranco, cavaloBranco, torreBranca}};

    for (int x = 0; x < TAM_TABULEIRO; x++)
    {
        for (int y = 0; y < TAM_TABULEIRO; y++)
        {
            // posicoesIniciais foi inserido ao exibirTabuleiro já com as peças em suas posições corretas
            tabuleiro[x][y] = posicoesIniciais[x][y];
        }
    }
}

int posicaoValida(int x, int y)
{
    return (x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO);
    // X e Y são maiores ou iguais a zero, ou seja, não é uma posição negativa.
    // X e Y são menores que 8, ou seja, estão dentro das linhas válidas do tabuleiro.
    // Se todas essas condições forem verdadeiras, a função retorna true.
    // Caso contrário, retorna false. Indicando uma posição não válida
}

int moverPeao(int inicioX, int fimX, char tipoPeca)
{
    int casasAndadas = inicioX - fimX;

    if (tipoPeca == peaoBranco)
    {
        if (inicioX == 6 && (casasAndadas == 1 || casasAndadas == 2))
        {
            return 1;
        }
        else if (casasAndadas != 1)
        {
            printf("Movimento invalido. Tente novamente.\n");
            return 0;
        }
    }
    else if (tipoPeca == peaoPreto)
    {
        if (inicioX == 1 && (casasAndadas == -1 || casasAndadas == -2))
        {
            return 1;
        }
        else if (casasAndadas != -1)
        {
            printf("Movimento invalido. Tente novamente.\n");
            return 0;
        }
    }

    return 1;
}

int moverCavalo(int inicioX, int inicioY, int fimX, int fimY)
{
    int casasAndadasX = fimX - inicioX;
    int casasAndadasY = fimY - inicioY;

    // Valida as casas entre as colunas e as linhas para fazer o movimento L
    if ((casasAndadasX == 2 && (casasAndadasY == 1 || casasAndadasY == -1)) ||
        (casasAndadasX == -2 && (casasAndadasY == 1 || casasAndadasY == -1)) ||
        (casasAndadasY == 2 && (casasAndadasX == 1 || casasAndadasX == -1)) ||
        (casasAndadasY == -2 && (casasAndadasX == 1 || casasAndadasX == -1)))
    {
        return 1;
    }
    else
    {
        printf("Movimento inválido. Tente novamente.\n");
        return 0;
    }
}

int moverBispo(int inicioX, int inicioY, int fimX, int fimY)
{
    int casasAndadasX = fimX - inicioX;
    int casasAndadasY = fimY - inicioY;

    // Valida as casas entre as colunas e as linhas para verificar a diagonal
    if (casasAndadasX == casasAndadasY || casasAndadasX == -casasAndadasY)
    {
        return 1;
    }
    else
    {
        printf("Movimento inválido. Tente novamente.\n");
        return 0;
    }
}

int moverTorre(int inicioX, int inicioY, int fimX, int fimY)
{
    // Valida se a torre continua na reta inicial (linha ou coluna) 
    if (inicioX == fimX || inicioY == fimY)
    {
        return 1;
    }
    else
    {
        printf("Movimento inválido. Tente novamente.\n");
        return 0;
    }
}

void moverPeca(int inicioX, int inicioY, int fimX, int fimY)
{
    char peca = tabuleiro[inicioX][inicioY];
    int movimentoValido;

    // Se a peça não for válida (A peça é a posição)
    if (!posicaoValida(inicioX, inicioY) || !posicaoValida(fimX, fimY))
    {
        printf("A posicao informada nao e valida, tente novamente!\n");
        return;
    }

    if (peca == peaoBranco)
    {
        movimentoValido = moverPeao(inicioX, fimX, peaoBranco);
    }
    if (peca == peaoPreto)
    {
        movimentoValido = moverPeao(inicioX, fimX, peaoPreto);
    }
    if (peca == cavaloBranco || peca == cavaloPreto)
    {
        movimentoValido = moverCavalo(inicioX, inicioY, fimX, fimY);
    }
    if (peca == bispoBranco || peca == bispoPreto)
    {
        movimentoValido = moverBispo(inicioX, inicioY, fimX, fimY);
    }
    if (peca == torreBranca || peca == torrePreta)
    {
        movimentoValido = moverTorre(inicioX, inicioY, fimX, fimY);
    }
    if (movimentoValido == 1)
    {
        turno++;
        // A peça inicial vai para o destino/fim
        tabuleiro[fimX][fimY] = tabuleiro[inicioX][inicioY];
        // A posição inicial recebe um espaço vazio
        tabuleiro[inicioX][inicioY] = espacoVazio;
    }
}

void obterMovimentoUsuario()
{
    // 3 por para caractere nulo de terminação
    char inicio[3];
    char fim[3];

    if (turno % 2 == 0)
    {
        printf("Turno das pecas brancas");
    }
    else
    {
        printf("Turno das pecas pretas");
    }

    printf("\nInsira a peca que sera movimentada: ");
    scanf("%s", inicio);

    printf("\nInsira para onde a peca sera movimentada: ");
    scanf("%s", fim);

    int inicioY = inicio[0] - 'a';
    // Calcula a coordenada Y (coluna) da posição inicial
    // subtraindo o valor ASCII do primeiro caractere de início pelo valor ASCII do caractere ‘a’.
    // Isso converte a letra da coluna (por exemplo, ‘a’, ‘b’, ‘c’) em um índice numérico (0, 1, 2).

    int inicioX = 8 - (inicio[1] - '0');
    // Calcula a coordenada X (linha) da posição inicial
    // subtraindo o valor ASCII do segundo caractere de início pelo valor ASCII do caractere ‘0’
    // em seguida, subtraindo o resultado de 8.
    // Isso converte o dígito da linha (por exemplo, ‘1’, ‘2’, ‘3’) em um índice numérico (0, 1, 2).

    int fimY = fim[0] - 'a';
    // mesmo processo do início Y
    int fimX = 8 - (fim[1] - '0');
    // mesmo processo do início X

    char peca = tabuleiro[inicioX][inicioY];

    if (turno % 2 == 0 && (peca == peaoPreto || peca == torrePreta || peca == cavaloPreto || peca == bispoPreto || peca == reiPreto || peca == damaPreta) || turno % 2 == 1 && (peca == peaoBranco || peca == torreBranca || peca == cavaloBranco || peca == bispoBranco || peca == reiBranco || peca == damaBranca))
    {
        printf("Nao e o turno desta peça. Por favor, tente novamente.\n");
        return;
    }

    if (tabuleiro[inicioX][inicioY] != espacoVazio && posicaoValida(inicioX, inicioY) && posicaoValida(fimX, fimY))
    {
        moverPeca(inicioX, inicioY, fimX, fimY);
    }
    else
    {
        printf("Movimento invalido. Por favor, tente novamente.\n");
    }
}

int main()
{
    iniciarTabuleiro();
    exibirTabuleiro();
    printf("\n");

    while (1)
    {
        obterMovimentoUsuario();
        exibirTabuleiro();
        printf("\n");
    }
}
