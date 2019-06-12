#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// "Variavel global" que determina o número de vetores a serem gerados
// com o intuito de obter as médias e mediana necessárias
#define N_TESTES 20

// Função que realiza a impressão dos vetores no final da execução
// caso o argumento [-p] esteja presente.
void imprime (int *A, int tamanho) {
    int i = 0;
    for (; i < tamanho; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// Função que gera um array de arrays (matriz) ordenados de forma crescente
int **geraArrayCrescente (int tamanho) {
    int **A, i, j;
    A = (int**) calloc(N_TESTES, sizeof(int*));
    for (i = 0; i < N_TESTES; i++) {
        A[i] = (int*) calloc(tamanho, sizeof(int));
        for (j = 1; j <= tamanho; j++) { A[i][j - 1] = j; }
    }
    return A;
}

// Função que gera um array de arrays (matriz) ordenados de forma decrescente
int **geraArrayDecrescente (int tamanho) {
    int **A, i, j;
    A = (int**) calloc(N_TESTES, sizeof(int*));
    for (i = 0; i < N_TESTES; i++) {
        A[i] = (int*) calloc(tamanho, sizeof(int));
        for (j = 0; j < tamanho; j++) {
            A[i][j] = tamanho - j;
        }
    }
    return A;
}

// Função que gera um array de arrays (matriz) ordenados de forma aleatória
int **geraArrayAleatorio (int tamanho) {
    int **A, i, j;
    A = (int**) calloc(N_TESTES, sizeof(int*));
    for (i = 0; i < N_TESTES; i++) {
        A[i] = (int*) calloc(tamanho, sizeof(int));
        for (j = 0; j < tamanho; j++) { A[i][j] = (rand() % tamanho * 10) + 1; }
    }
    return A;
}
