#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("=== TABULEIRO ===\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0}; // Inicializa com água (0)

    int navioHorizontal[TAM_NAVIO] = {3, 3, 3};
    int navioVertical[TAM_NAVIO] = {3, 3, 3};

    // Coordenadas iniciais
    int linhaH = 2, colunaH = 4; // Navio horizontal começa na posição (2,4)
    int linhaV = 5, colunaV = 7; // Navio vertical começa na posição (5,7)

    // Verificações de limite para navios
    if (colunaH + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: Navio horizontal ultrapassa os limites do tabuleiro.\n");
        return 1;
    }
    if (linhaV + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: Navio vertical ultrapassa os limites do tabuleiro.\n");
        return 1;
    }

    // Verifica se haverá sobreposição
    int sobreposicao = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linhaH][colunaH + i] == 3 || tabuleiro[linhaV + i][colunaV] == 3) {
            sobreposicao = 1;
            break;
        }
    }
    if (sobreposicao) {
        printf("Erro: Sobreposição detectada entre navios.\n");
        return 1;
    }

    // Posiciona o navio horizontal
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }

    // Posiciona o navio vertical
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }

    // Exibe o tabuleiro
    exibirTabuleiro(tabuleiro);

    return 0;
}