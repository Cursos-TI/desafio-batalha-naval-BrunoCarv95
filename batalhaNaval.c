#include <stdio.h>
#include <stdlib.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n=== TABULEIRO ===\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 3)
                printf("N ");  // Navio
            else if (tabuleiro[i][j] == 9)
                printf("9 ");  // Área atingida
            else if (tabuleiro[i][j] == -1)
                printf("X ");  // Acerto em navio
            else
                printf("0 ");
        }
        printf("\n");
    }
}

int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha[], int coluna[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (linha[i] < 0 || linha[i] >= TAM_TABULEIRO || coluna[i] < 0 || coluna[i] >= TAM_TABULEIRO)
            return 0;
        if (tabuleiro[linha[i]][coluna[i]] == 3)
            return 0;
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

void habilidadeCone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (i + j >= 2 && j - i <= 2 && i <= 2) ? 1 : 0;
}

void habilidadeCruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

void habilidadeOctaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matriz[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[5][5], int centroLinha, int centroColuna, const char* nome) {
    printf("\nAplicando habilidade: %s no centro (%d, %d)\n", nome, centroLinha, centroColuna);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int linha = centroLinha + (i - 2);
                int coluna = centroColuna + (j - 2);
                if (linha >= 0 && linha < TAM_TABULEIRO && coluna >= 0 && coluna < TAM_TABULEIRO) {
                    if (tabuleiro[linha][coluna] == 3)  // Acertou navio
                        tabuleiro[linha][coluna] = -1;
                    else if (tabuleiro[linha][coluna] == 0)
                        tabuleiro[linha][coluna] = 9;  // Apenas atingido
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // === NAVIOS ===
    int linhaH[TAM_NAVIO] = {1, 1, 1};
    int colunaH[TAM_NAVIO] = {2, 3, 4};

    int linhaV[TAM_NAVIO] = {4, 5, 6};
    int colunaV[TAM_NAVIO] = {5, 5, 5};

    int linhaD1[TAM_NAVIO] = {0, 1, 2};
    int colunaD1[TAM_NAVIO] = {0, 1, 2};

    int linhaD2[TAM_NAVIO] = {2, 3, 4};
    int colunaD2[TAM_NAVIO] = {7, 6, 5};

    if (!podePosicionar(tabuleiro, linhaH, colunaH, TAM_NAVIO) ||
        !podePosicionar(tabuleiro, linhaV, colunaV, TAM_NAVIO) ||
        !podePosicionar(tabuleiro, linhaD1, colunaD1, TAM_NAVIO) ||
        !podePosicionar(tabuleiro, linhaD2, colunaD2, TAM_NAVIO)) {
        printf("Erro ao posicionar navios. Verifique sobreposição ou limites.\n");
        return 1;
    }

    posicionarNavio(tabuleiro, linhaH, colunaH, TAM_NAVIO, "Navio Horizontal");
    posicionarNavio(tabuleiro, linhaV, colunaV, TAM_NAVIO, "Navio Vertical");
    posicionarNavio(tabuleiro, linhaD1, colunaD1, TAM_NAVIO, "Navio Diagonal Principal");
    posicionarNavio(tabuleiro, linhaD2, colunaD2, TAM_NAVIO, "Navio Diagonal Secundária");

    exibirTabuleiro(tabuleiro);

    // === MATRIZES DE HABILIDADES ===
    int cone[5][5], cruz[5][5], octaedro[5][5];
    habilidadeCone(cone);
    habilidadeCruz(cruz);
    habilidadeOctaedro(octaedro);

    // === ATAQUES ===
    aplicarHabilidade(tabuleiro, cone, 2, 2, "Cone");
    aplicarHabilidade(tabuleiro, cruz, 5, 5, "Cruz");
    aplicarHabilidade(tabuleiro, octaedro, 1, 4, "Octaedro");

    // === TABULEIRO APÓS ATAQUES ===
    exibirTabuleiro(tabuleiro);

    return 0;
}