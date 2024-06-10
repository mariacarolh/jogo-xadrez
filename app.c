#include <stdio.h>
#include <stdlib.h> // Lib para limpar a tela

#define TAM_TABULEIRO 8                // Tamanho padrão do tabuleiro
#define MAGENTA "\x1b[38;5;200m"       // Definindo a cor rosa
#define VERMELHO "\x1b[38;5;9m"        // Definindo a cor vermelha
#define VERMELHO_ESCURO "\x1b[38;5;1m" // Definindo a cor vermelho escuro
#define AMARELO "\x1b[38;5;226m"       // Definindo a cor amarela
#define VERDE "\x1b[38;5;46m"          // Definindo a cor verde
#define RESET "\x1B[0m"                // Reset de cor

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

int turno = 0;         // Variável para turnos (0 brancas e 1 pretas)
int pontosBrancas = 0; // Variável para pontos das peças brancas
int pontosPretas = 0;  // Variável para pontos das peças pretas

char mensagemErro[100] = "";                  // Mensagens de erros
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

    if (mensagemErro[0] != '\0') // Se a mensagem de erro não estiver vazia será exibido o aviso
    {
        printf("\n" VERMELHO "  %s\n" RESET, mensagemErro);
    }
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

int pecaAliada(char peca, char pecaDestino)
{
    // Verifica se ambas as peças são maiúsculas ou minúsculas.
    // Se a peça inicial for do mesmo tamanho (caps-lock) da final, é aliado.
    return ((peca >= 'a' && peca <= 'z' && pecaDestino >= 'a' && pecaDestino <= 'z') ||
            (peca >= 'A' && peca <= 'Z' && pecaDestino >= 'A' && pecaDestino <= 'Z'));
}

int caminhoLinhaColunaLivre(char inicioX, char inicioY, char fimX, char fimY)
{
    // Verifica se o caminho horizontal está livre
    if (inicioX == fimX)
    {
        // é necessário verificar todas as casas entre inicioX e fimX
        // então verificamos qual dos dois é o menor (menorX) e qual é o maior (maiorX)
        // e aí iteramos de menorX + 1 até maiorX - 1 para verificar se há alguma peça bloqueando o caminho.
        int menorY = inicioY < fimY ? inicioY : fimY;
        int maiorY = inicioY > fimY ? inicioY : fimY;

        for (int y = menorY + 1; y < maiorY; y++)
        {
            if (tabuleiro[inicioX][y] != espacoVazio)
            {
                snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, existe uma peca no caminho!");
                return 0; // Caminho bloqueado
            }
        }
    }
    if (inicioY == fimY)
    {
        int menorX = inicioX < fimX ? inicioX : fimX;
        int maiorX = inicioX > fimX ? inicioX : fimX;

        for (int x = menorX + 1; x < maiorX; x++)
        {
            if (tabuleiro[x][inicioY] != espacoVazio)
            {
                snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, existe uma peca no caminho!");
                return 0;
            }
        }
    }
    return 1; // Caminho livre
}

int caminhoDiagonalLivre(char inicioX, char inicioY, char fimX, char fimY)
{
    int casasAndadasX = (fimX > inicioX) ? 1 : -1;
    int casasAndadasY = (fimY > inicioY) ? 1 : -1;

    int x = inicioX + casasAndadasX;
    int y = inicioY + casasAndadasY;

    // Loop para percorrer o caminho diagonal
    while (x != fimX || y != fimY)
    {
        // Se a posição atual não estiver vazia, retorna 0 (caminho bloqueado)
        if (tabuleiro[x][y] != espacoVazio)
        {
            snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, existe uma peca no caminho!");
            return 0;
        }
        // Muda as posições para a próxima casa na diagonal
        x += casasAndadasX;
        y += casasAndadasY;

        // Se a posição não for válida, interrompe o loop
        if (!posicaoValida(x, y))
        {
            break;
        }
    }

    // Se todas as casas na diagonal estiverem livres, retorna 1
    return 1;
}

int verificarCheque(char rei, char adversarioPeao, char adversarioTorre, char adversarioCavalo, char adversarioBispo, char adversarioDama)
{
    int reiX, reiY;
    for (int x = 0; x < TAM_TABULEIRO; x++)
    {
        for (int y = 0; y < TAM_TABULEIRO; y++)
        {
            if (tabuleiro[x][y] == rei)
            {
                reiX = x;
                reiY = y;
            }
        }
    }

    // Verificar peões adversários
    int direcaoPeao = (adversarioPeao == 'p') ? 1 : -1;
    if (posicaoValida(reiX + direcaoPeao, reiY - 1) && tabuleiro[reiX + direcaoPeao][reiY - 1] == adversarioPeao)
        return 1;
    if (posicaoValida(reiX + direcaoPeao, reiY + 1) && tabuleiro[reiX + direcaoPeao][reiY + 1] == adversarioPeao)
        return 1;

    // Verificar cavalo adversário
    int movimentosCavalo[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    for (int i = 0; i < 8; i++)
    {
        int novoX = reiX + movimentosCavalo[i][0];
        int novoY = reiY + movimentosCavalo[i][1];
        if (posicaoValida(novoX, novoY) && tabuleiro[novoX][novoY] == adversarioCavalo)
            return 1;
    }

    // Verificar linha/coluna (torre e dama)
    for (int x = reiX + 1; x < TAM_TABULEIRO; x++)
    {
        if (tabuleiro[x][reiY] == adversarioTorre || tabuleiro[x][reiY] == adversarioDama)
            return 1;
        if (tabuleiro[x][reiY] != espacoVazio)
            break;
    }
    for (int x = reiX - 1; x >= 0; x--)
    {
        if (tabuleiro[x][reiY] == adversarioTorre || tabuleiro[x][reiY] == adversarioDama)
            return 1;
        if (tabuleiro[x][reiY] != espacoVazio)
            break;
    }
    for (int y = reiY + 1; y < TAM_TABULEIRO; y++)
    {
        if (tabuleiro[reiX][y] == adversarioTorre || tabuleiro[reiX][y] == adversarioDama)
            return 1;
        if (tabuleiro[reiX][y] != espacoVazio)
            break;
    }
    for (int y = reiY - 1; y >= 0; y--)
    {
        if (tabuleiro[reiX][y] == adversarioTorre || tabuleiro[reiX][y] == adversarioDama)
            return 1;
        if (tabuleiro[reiX][y] != espacoVazio)
            break;
    }

    // Verificar diagonais (bispo e dama)
    for (int i = 1; posicaoValida(reiX + i, reiY + i); i++)
    {
        if (tabuleiro[reiX + i][reiY + i] == adversarioBispo || tabuleiro[reiX + i][reiY + i] == adversarioDama)
            return 1;
        if (tabuleiro[reiX + i][reiY + i] != espacoVazio)
            break;
    }
    for (int i = 1; posicaoValida(reiX - i, reiY - i); i++)
    {
        if (tabuleiro[reiX - i][reiY - i] == adversarioBispo || tabuleiro[reiX - i][reiY - i] == adversarioDama)
            return 1;
        if (tabuleiro[reiX - i][reiY - i] != espacoVazio)
            break;
    }
    for (int i = 1; posicaoValida(reiX + i, reiY - i); i++)
    {
        if (tabuleiro[reiX + i][reiY - i] == adversarioBispo || tabuleiro[reiX + i][reiY - i] == adversarioDama)
            return 1;
        if (tabuleiro[reiX + i][reiY - i] != espacoVazio)
            break;
    }
    for (int i = 1; posicaoValida(reiX - i, reiY + i); i++)
    {
        if (tabuleiro[reiX - i][reiY + i] == adversarioBispo || tabuleiro[reiX - i][reiY + i] == adversarioDama)
            return 1;
        if (tabuleiro[reiX - i][reiY + i] != espacoVazio)
            break;
    }

    return 0;
}

int verificarChequeMate(char rei, char adversarioPeao, char adversarioTorre, char adversarioCavalo, char adversarioBispo, char adversarioDama)
{
    int reiX, reiY;
    for (int x = 0; x < TAM_TABULEIRO; x++)
    {
        for (int y = 0; y < TAM_TABULEIRO; y++)
        {
            if (tabuleiro[x][y] == rei)
            {
                reiX = x;
                reiY = y;
                break;
            }
        }
    }

    // Verificar todos os movimentos possíveis do rei
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            int novoX = reiX + i;
            int novoY = reiY + j;

            if (posicaoValida(novoX, novoY) && !pecaAliada(rei, tabuleiro[novoX][novoY]))
            {
                // Simula o movimento
                char pecaOrigem = tabuleiro[novoX][novoY];
                tabuleiro[novoX][novoY] = rei;
                tabuleiro[reiX][reiY] = espacoVazio;

                // Verifica se o rei ainda está em cheque
                int cheque = verificarCheque(rei, adversarioPeao, adversarioTorre, adversarioCavalo, adversarioBispo, adversarioDama);

                // Reverte o movimento
                tabuleiro[reiX][reiY] = rei;
                tabuleiro[novoX][novoY] = pecaOrigem;

                if (!cheque)
                {
                    return 0; // O rei pode escapar do cheque
                }
            }
        }
    }

    // Se nenhum movimento é possível para sair do cheque
    return 1;
}

void verificarCheques()
{
    if (verificarCheque(reiBranco, peaoPreto, torrePreta, cavaloPreto, bispoPreto, damaPreta))
    {
        if (verificarChequeMate(reiBranco, peaoPreto, torrePreta, cavaloPreto, bispoPreto, damaPreta))
        {
            snprintf(mensagemErro, sizeof(mensagemErro), RESET VERDE "Rei Branco esta em cheque-mate! Pretas ganham!" RESET);
            pontosPretas++;
        }
        else
        {
            snprintf(mensagemErro, sizeof(mensagemErro), RESET VERMELHO_ESCURO "Rei Branco esta em cheque!" RESET);
        }
    }
    else if (verificarCheque(reiPreto, peaoBranco, torreBranca, cavaloBranco, bispoBranco, damaBranca))
    {
        if (verificarChequeMate(reiPreto, peaoBranco, torreBranca, cavaloBranco, bispoBranco, damaBranca))
        {
            snprintf(mensagemErro, sizeof(mensagemErro), RESET VERDE "Rei Preto esta em cheque-mate! Brancas ganham!" RESET);
            pontosBrancas++;
        }
        else
        {
            snprintf(mensagemErro, sizeof(mensagemErro), RESET VERMELHO_ESCURO "Rei Preto esta em cheque!" RESET);
        }
    }
}

int impedirTraicao(int inicioX, int inicioY, int fimX, int fimY)
{
    char pecaOrigem = tabuleiro[inicioX][inicioY];
    char pecaDestino = tabuleiro[fimX][fimY];

    // Simula o movimento
    tabuleiro[fimX][fimY] = pecaOrigem;
    tabuleiro[inicioX][inicioY] = espacoVazio;

    // Verifica se o movimento deixa o rei em cheque
    int cheque = 0;
    if (pecaOrigem >= 'a' && pecaOrigem <= 'z') // Peça preta
    {
        cheque = verificarCheque(reiPreto, peaoBranco, torreBranca, cavaloBranco, bispoBranco, damaBranca);
    }
    else if (pecaOrigem >= 'A' && pecaOrigem <= 'Z') // Peça branca
    {
        cheque = verificarCheque(reiBranco, peaoPreto, torrePreta, cavaloPreto, bispoPreto, damaPreta);
    }

    // Reverte o movimento
    tabuleiro[inicioX][inicioY] = pecaOrigem;
    tabuleiro[fimX][fimY] = pecaDestino;

    return cheque;
}

int moverPeao(int inicioX, int inicioY, int fimX, int fimY, char tipoPeca)
{
    int casasAndadasX = inicioX - fimX;
    int casasAndadasY = fimY - inicioY;
    char pecaDestino = tabuleiro[fimX][fimY];

    if (tipoPeca == peaoBranco)
    {
        // Verifica se o peão branco está na posição inicial
        if (inicioX == 6)
        {
            // Movimento de uma casa para frente
            if (casasAndadasX == 1 && casasAndadasY == 0 && tabuleiro[fimX][fimY] == espacoVazio)
            {
                return 1;
            }
            // Movimento de duas casas para frente (apenas no primeiro movimento)
            if (casasAndadasX == 2 && casasAndadasY == 0 && tabuleiro[fimX][fimY] == espacoVazio && tabuleiro[fimX + 1][fimY] == espacoVazio)
            {
                return 1;
            }
        }
        else
        {
            // Movimento de uma casa para frente
            if (casasAndadasX == 1 && casasAndadasY == 0 && tabuleiro[fimX][fimY] == espacoVazio)
            {
                return 1;
            }
        }

        // Movimento de captura na diagonal (caso não seja uma peça aliada)
        if (casasAndadasX == 1 && (casasAndadasY == 1 || casasAndadasY == -1) && pecaDestino != espacoVazio && !pecaAliada(tipoPeca, pecaDestino))
        {
            return 1;
        }
    }
    else if (tipoPeca == peaoPreto)
    {
        // Verifica se o peão preto está na posição inicial
        if (inicioX == 1)
        {
            // Movimento de uma casa para frente
            if (casasAndadasX == -1 && casasAndadasY == 0 && tabuleiro[fimX][fimY] == espacoVazio)
            {
                return 1;
            }
            // Movimento de duas casas para frente (apenas no primeiro movimento)
            if (casasAndadasX == -2 && casasAndadasY == 0 && tabuleiro[fimX][fimY] == espacoVazio && tabuleiro[fimX - 1][fimY] == espacoVazio)
            {
                return 1;
            }
        }
        else
        {
            // Movimento de uma casa para frente
            if (casasAndadasX == -1 && casasAndadasY == 0 && tabuleiro[fimX][fimY] == espacoVazio)
            {
                return 1;
            }
        }

        // Movimento de captura na diagonal
        if (casasAndadasX == -1 && (casasAndadasY == 1 || casasAndadasY == -1) && pecaDestino != espacoVazio && !pecaAliada(tipoPeca, pecaDestino))
        {
            return 1;
        }
    }

    snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
    return 0; // Movimento inválido
}

void promoverPeao(int x, int y, char tipoPeca)
{
    char novaPeca;
    int pecaValida = 0;

    // Equanto não for escolhido uma peça válida entre as opções, o jogo não irá prosseguir
    while (!pecaValida)
    {
        printf(AMARELO "Promocao! Escolha a nova peca \n D - Dama\n T - Torre\n B - Bispo\n C - Cavalo: " RESET);
        scanf(" %c", &novaPeca);

        switch (novaPeca)
        {
        case 'D':
        case 'd':
            novaPeca = (tipoPeca == peaoBranco) ? damaBranca : damaPreta;
            pecaValida = 1;
            break;
        case 'T':
        case 't':
            novaPeca = (tipoPeca == peaoBranco) ? torreBranca : torrePreta;
            pecaValida = 1;
            break;
        case 'B':
        case 'b':
            novaPeca = (tipoPeca == peaoBranco) ? bispoBranco : bispoPreto;
            pecaValida = 1;
            break;
        case 'C':
        case 'c':
            novaPeca = (tipoPeca == peaoBranco) ? cavaloBranco : cavaloPreto;
            pecaValida = 1;
            break;
        default:
            printf(VERMELHO "Entrada invalida! Tente novamente.\n" RESET);
            break;
        }
    }
    // Peça atual vira peça escolhida
    tabuleiro[x][y] = novaPeca;
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
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
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
        return caminhoDiagonalLivre(inicioX, inicioY, fimX, fimY);
    }
    else
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
        return 0;
    }
}

int moverTorre(int inicioX, int inicioY, int fimX, int fimY)
{
    // Valida se a torre continua na reta inicial (linha ou coluna)
    if (inicioX == fimX || inicioY == fimY)
    {
        return caminhoLinhaColunaLivre(inicioX, inicioY, fimX, fimY);
    }
    else
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
        return 0;
    }
}

int moverDama(int inicioX, int inicioY, int fimX, int fimY)
{
    int casasAndadasX = fimX - inicioX;
    int casasAndadasY = fimY - inicioY;

    // Segue a combinação das regras do bispo e da torre
    if ((inicioX == fimX || inicioY == fimY) || (casasAndadasX == casasAndadasY || casasAndadasX == -casasAndadasY))
    {
        return (caminhoDiagonalLivre(inicioX, inicioY, fimX, fimY) && caminhoLinhaColunaLivre(inicioX, inicioY, fimX, fimY));
    }
    else
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
        return 0;
    }
}

int moverRei(int inicioX, int inicioY, int fimX, int fimY)
{
    int casasAndadasX = fimX - inicioX;
    int casasAndadasY = fimY - inicioY;

    if ((casasAndadasX >= -1 && casasAndadasX <= 1) && (casasAndadasY >= -1 && casasAndadasY <= 1))
    {
        return 1;
    }
    else
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
        return 0;
    }
}

void moverPeca(int inicioX, int inicioY, int fimX, int fimY)
{
    char peca = tabuleiro[inicioX][inicioY];
    char pecaDestino = tabuleiro[fimX][fimY];
    int movimentoValido = 0;

    // Se a peça não for válida (A peça é a posição)
    if (!posicaoValida(inicioX, inicioY) || !posicaoValida(fimX, fimY))
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "A posicao informada nao e valida, tente novamente!");
        return;
    }
    if (pecaDestino != espacoVazio && pecaAliada(peca, pecaDestino))
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, nao e possivel atacar pecas aliadas!");
        return;
    }
    if (impedirTraicao(inicioX, inicioY, fimX, fimY))
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, nao e permitido deixar o rei em cheque!");
        return;
    }

    if (peca == peaoBranco)
    {
        movimentoValido = moverPeao(inicioX, inicioY, fimX, fimY, peaoBranco);
    }
    else if (peca == peaoPreto)
    {
        movimentoValido = moverPeao(inicioX, inicioY, fimX, fimY, peaoPreto);
    }
    else if (peca == cavaloBranco || peca == cavaloPreto)
    {
        movimentoValido = moverCavalo(inicioX, inicioY, fimX, fimY);
    }
    else if (peca == bispoBranco || peca == bispoPreto)
    {
        movimentoValido = moverBispo(inicioX, inicioY, fimX, fimY);
    }
    else if (peca == torreBranca || peca == torrePreta)
    {
        movimentoValido = moverTorre(inicioX, inicioY, fimX, fimY);
    }
    else if (peca == damaBranca || peca == damaPreta)
    {
        movimentoValido = moverDama(inicioX, inicioY, fimX, fimY);
    }
    else if (peca == reiBranco || peca == reiPreto)
    {
        movimentoValido = moverRei(inicioX, inicioY, fimX, fimY);
    }

    if (movimentoValido == 1)
    {
        turno++;
        // A peça inicial vai para o destino/fim
        tabuleiro[fimX][fimY] = tabuleiro[inicioX][inicioY];
        // A posição inicial recebe um espaço vazio
        tabuleiro[inicioX][inicioY] = espacoVazio;
        // Limpar mensagem de erro depois de um movimento válido
        mensagemErro[0] = '\0';

        // Verifica se um peão chegou ao fim do tabuleiro para promover
        if ((peca == peaoBranco && fimX == 0) || (peca == peaoPreto && fimX == 7))
        {
            promoverPeao(fimX, fimY, peca);
        }
    }
}

void obterMovimentoUsuario()
{
    // 3 para caractere nulo de terminação
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
    scanf("%2s", inicio); // 2s para ler uma string de no máximo dois caracteres

    printf("\nInsira para onde a peca sera movimentada: ");
    scanf("%2s", fim);

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
        snprintf(mensagemErro, sizeof(mensagemErro), "Nao e o turno desta peca, tente novamente!");
        return;
    }

    if (tabuleiro[inicioX][inicioY] != espacoVazio && posicaoValida(inicioX, inicioY) && posicaoValida(fimX, fimY))
    {
        moverPeca(inicioX, inicioY, fimX, fimY);
    }
    else
    {
        snprintf(mensagemErro, sizeof(mensagemErro), "Movimento invalido, tente novamente!");
    }
}

void iniciarJogo()
{
    iniciarTabuleiro();
    exibirTabuleiro();
    printf("\n");
    while (1)
    {
        obterMovimentoUsuario();
        verificarCheques();
        exibirTabuleiro();
        printf("\n");
    }
}

void exibirPontuacao()
{
    limparTela();
    printf(" Pontuacao:\n");
    printf(" -----------------------------\n");
    printf(" Brancas: %d\n", pontosBrancas);
    printf(" -----------------------------\n");
    printf(MAGENTA " Pretas" RESET ":%d\n", pontosPretas);
    printf(" -----------------------------\n\n");

    printf(" Digite qualquer tecla para retornar ao menu\n");
    getchar();
    getchar();
}
void menu()
{
    limparTela();
    while (1)
    {
        limparTela();
        printf(" _______________________________\n");
        printf(" __  __         _              \n");
        printf(" \\ \\/ /__ _  __| |_ __ ___ ____\n");
        printf("  \\  // _` |/ _` | '__/ _ \\_  /\n");
        printf("  /  \\ (_| | (_| | | |  __// / \n");
        printf(" /_/\\_\\__,_|\\__,_|_|  \\___/___|\n");
        printf(" _______________________________\n");

        int opcao;
        printf(" \n Escolha uma opcao:\n");
        printf(" \n -----------------------------");
        printf(" \n 1 - Iniciar um novo jogo\n");
        printf(" -----------------------------\n");
        printf(" 2 - Ver placar atual\n");
        printf(" -----------------------------\n");
        printf(" 3 - Regras \n");
        printf(" -----------------------------\n");
        printf(" 4 - Sair\n");

        printf("\n Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            iniciarJogo();
        case 2:
            exibirPontuacao();
        case 4:
            printf(VERDE "\nObrigado por jogar, ate mais!\n" RESET);
            exit(0);
        }
    }
}

int main()
{
    menu();
}