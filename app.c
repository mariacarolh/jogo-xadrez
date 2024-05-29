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

int posicaoValida(int x, int y)
{
    return (x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO); 
    // X e Y são maiores ou iguais a zero, ou seja, não é uma posição negativa.
    // X e Y são menores que 8, ou seja, estão dentro das linhas válidas do tabuleiro.
    // Se todas essas condições forem verdadeiras, a função retorna true. 
    // Caso contrário, retorna false. Indicando uma posição não válida
}

void moverPeca(int inicioX, int inicioY, int fimX, int fimY)
{
    // Se a peça não for válida, mostre: (A peça é a posição)
    if (!posicaoValida(inicioX, inicioY) || !posicaoValida(fimX, fimY)) 
    {
        printf("A posicao informada nao e valida, tente novamente!\n");
        return;
    }

    // A peça inicial vai para o destino/fim 
    tabuleiro[fimX][fimY] = tabuleiro[inicioX][inicioY];
    // A posição inicial recebe um espaço vazio
    tabuleiro[inicioX][inicioY] = eV;
}

void obterMovimentoUsuario()
{
    // 3 por para caractere nulo de terminação
    char inicio[3];
    char fim[3];

    printf("Insira a peca que sera movimentada: ");
    scanf("%s", inicio);

    printf("Insira para onde a peca sera movimentada: ");
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

    moverPeca(inicioX, inicioY, fimX, fimY);
}

int main()
{
    iniciarTabuleiro();
    exibirTabuleiro();
    obterMovimentoUsuario();
    exibirTabuleiro();
}