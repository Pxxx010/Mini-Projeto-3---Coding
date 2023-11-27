#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 3

// Dar start no tabuleiro
void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

// Imprimindo o tabuleiro no console
void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c", tabuleiro[i][j]);
            if (j < TAMANHO - 1) printf("|");
        }
        printf("\n");
        if (i < TAMANHO - 1) printf("-----\n");
    }
}

// Verificando se á um vencedor
bool verificarVencedor(char tabuleiro[TAMANHO][TAMANHO], char jogador) {
    for (int i = 0; i < TAMANHO; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) return true; // Verifica as linhas
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) return true; // Verifica as colunas
    }
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) return true;    // Verifica as diagonais
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) return true;    // Verifica as diagonais
    return false;
}

// Verifica se o tabuleiro esta cheio
bool tabuleiroCheio(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) { // Primeiro For verifica se as linhas do tabuleiro esta cheia
        for (int j = 0; j < TAMANHO; j++) { // Segundo For verifica se as colunas do tabuleiro esta cheia
            if (tabuleiro[i][j] == ' ') return false; // Return sempre false, se houver true tabuleiro esta cheio
        }
    }
    return true;
}

// Imprimi quem foi o vencedor
void imprimirVitoria(char nome[]) {
    printf("\033[31m");
    printf("PARABENS ");
    printf("\033[0m");
    for (int i = 0; nome[i] != '\0'; i++) {
        printf("\033[31m");
        printf("%c", toupper(nome[i])); 
        printf("\033[0m");
    }
    printf("\033[31m"); 
    printf(", VOCE VENCEU!!!\n");
    printf("\033[0m"); 
}


// Main
int main() {
    char tabuleiro[TAMANHO][TAMANHO];
    char jogadorAtual = 'X';
    int linha, coluna;
    bool jogoTerminou = false;
    char nomeJogador1[50], nomeJogador2[50];

    printf("Digite o nome do jogador 1 (X): ");
    fgets(nomeJogador1, 50, stdin);
    nomeJogador1[strcspn(nomeJogador1, "\n")] = 0; // Apaga a linha

    printf("Digite o nome do jogador 2 (O): ");
    fgets(nomeJogador2, 50, stdin);
    nomeJogador2[strcspn(nomeJogador2, "\n")] = 0; // Apaga a linha

    inicializarTabuleiro(tabuleiro);

    while (!jogoTerminou) {
        imprimirTabuleiro(tabuleiro);
        printf("Jogador %c (%s), escolha uma linha e uma coluna [1-3]: ", jogadorAtual, // Informa o nome do jogador e solicita a linha e a coluna para efetuar a jogada
               (jogadorAtual == 'X') ? nomeJogador1 : nomeJogador2);
        scanf("%d %d", &linha, &coluna);
        while (getchar() != '\n'); // Clear Buffer

        if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || tabuleiro[linha - 1][coluna - 1] != ' ') {
            printf("Jogada inválida. Tente novamente.\n"); // Msg de erro
            continue;
        }

        tabuleiro[linha - 1][coluna - 1] = jogadorAtual;

        if (verificarVencedor(tabuleiro, jogadorAtual)) {
            imprimirTabuleiro(tabuleiro);
            imprimirVitoria((jogadorAtual == 'X') ? nomeJogador1 : nomeJogador2);
            jogoTerminou = true;
        } else if (tabuleiroCheio(tabuleiro)) {
            imprimirTabuleiro(tabuleiro);
            printf("Empate!\n");
            jogoTerminou = true;
        }

        jogadorAtual = (jogadorAtual == 'X') ? 'O' : 'X';
    }

    return 0;
}