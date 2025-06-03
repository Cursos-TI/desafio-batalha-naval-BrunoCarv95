#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n=== TABULEIRO ===\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha[], int coluna[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (linha[i] < 0 || linha[i] >= TAM_TABULEIRO || coluna[i] < 0 || coluna[i] >= TAM_TABULEIRO) {
            return 0;
        }
        if (tabuleiro[linha[i]][coluna[i]] == 3) {
            return 0;
        }
    }
    return 1;
}

void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha[], int coluna[], int tamanho, const char* nome) {
    printf("Coordenadas do %s:\n", nome);
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linha[i]][coluna[i]] = 3;
        printf("(%d, %d)\n", linha[i], coluna[i]);
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Navio 1 - Horizontal 
    int linhaH[TAM_NAVIO] = {8, 8, 8};
    int colunaH[TAM_NAVIO] = {2, 3, 4};

    // Navio 2 - Vertical 
    int linhaV[TAM_NAVIO] = {5, 6, 7};
    int colunaV[TAM_NAVIO] = {7, 7, 7};

    // Navio 3 - Diagonal 
    int linhaD1[TAM_NAVIO] = {0, 1, 2};
    int colunaD1[TAM_NAVIO] = {0, 1, 2};

    // Navio 4 - Diagonal 
    int linhaD2[TAM_NAVIO] = {2, 3, 4};
    int colunaD2[TAM_NAVIO] = {7, 6, 5};

    // Validar e posicionar cada navio
    if (!podePosicionar(tabuleiro, linhaH, colunaH, TAM_NAVIO)) {
        printf("Erro: Navio horizontal fora do tabuleiro ou sobreposição.\n");
        return 1;
    }
    posicionarNavio(tabuleiro, linhaH, colunaH, TAM_NAVIO, "Navio Horizontal");

    if (!podePosicionar(tabuleiro, linhaV, colunaV, TAM_NAVIO)) {
        printf("Erro: Navio vertical fora do tabuleiro ou sobreposição.\n");
        return 1;
    }
    posicionarNavio(tabuleiro, linhaV, colunaV, TAM_NAVIO, "Navio Vertical");

    if (!podePosicionar(tabuleiro, linhaD1, colunaD1, TAM_NAVIO)) {
        printf("Erro: Navio diagonal 1 fora do tabuleiro ou sobreposição.\n");
        return 1;
    }
    posicionarNavio(tabuleiro, linhaD1, colunaD1, TAM_NAVIO, "Navio Diagonal Principal");

    if (!podePosicionar(tabuleiro, linhaD2, colunaD2, TAM_NAVIO)) {
        printf("Erro: Navio diagonal 2 fora do tabuleiro ou sobreposição.\n");
        return 1;
    }
    posicionarNavio(tabuleiro, linhaD2, colunaD2, TAM_NAVIO, "Navio Diagonal Secundária");

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}