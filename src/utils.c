#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "includes/funcoes.h"
#include "includes/pilha.h"

#define N_TESTES 2

void imprime (int *A, int tamanho) {
    int i = 0;
    for (; i < tamanho; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int **geraArrayCrescente (int tamanho) {
    int **A, i, j;
    A = (int**) calloc(N_TESTES, sizeof(int*));
    for (i = 0; i < N_TESTES; i++) {
        A[i] = (int*) calloc(tamanho, sizeof(int));
        for (j = 1; j <= tamanho; j++) { A[i][j - 1] = j; }
    }
    return A;
}

int **geraArrayDecrescente (int tamanho) {
    int **A, i, j;
    A = (int**) calloc(N_TESTES, sizeof(int*));
    for (i = 0; i < N_TESTES; i++) {
        A[i] = (int*) calloc(tamanho, sizeof(int));
        for (j = 0; j < tamanho; j++) { A[i][j] = tamanho - j; }
    }
    return A;
}

int **geraArrayAleatorio (int tamanho) {
    int **A, i, j;
    A = (int**) calloc(N_TESTES, sizeof(int*));
    for (i = 0; i < N_TESTES; i++) {
        A[i] = (int*) calloc(tamanho, sizeof(int));
        for (j = 0; j < tamanho; j++) { A[i][j] = (rand() % tamanho * 10) + 1; }
    }
    return A;
}

int initSort (int argc, char *argv[]) {
    struct timespec start, end;
    long *elapsed_time, numeroTrocasTotal;
    double comparacoesTotais = 0.0;
    int **A, **B, i, j, tamanho, imprimirArray = 0;
    char *tipoOrdenacao, *organizacaoVetor;

    tipoOrdenacao = (char*) malloc(sizeof(char));
    organizacaoVetor = (char*) malloc(sizeof(char));
    tamanho = atoi(argv[3]);
    strcpy(tipoOrdenacao, argv[1]);
    strcpy(organizacaoVetor, argv[2]);

    elapsed_time = (long*) calloc(N_TESTES, sizeof(long));

    // Gerando 20 arrays para pegar a mediana de tempo
    if (strcmp(organizacaoVetor, "OrdC") == 0) { A = geraArrayCrescente(tamanho); }
    if (strcmp(organizacaoVetor, "OrdD") == 0) { A = geraArrayDecrescente(tamanho); }
    if (strcmp(organizacaoVetor, "Ale") == 0) {  A = geraArrayAleatorio(tamanho); }

    // Printar arrays no final:     
    if (argc == 5 && strcmp(argv[4], "-p") == 0) {
        imprimirArray = 1;
        B = (int**) malloc(N_TESTES * sizeof(int*));
        for (i = 0; i < N_TESTES; i++) {
            B[i] = (int*) malloc(tamanho * sizeof(int));
            for (j = 0; j < tamanho; j++) {
                B[i][j] = A[i][j];
            }
        }
    }

    long nTrocas;
    numeroTrocasTotal = 0;
    for (int i = 0; i < N_TESTES; i++) {
        clock_gettime(CLOCK_REALTIME, &start);
        
        comparacoesTotais += QuickSortContainer(A[i], tamanho, tipoOrdenacao, &numeroTrocasTotal)/(double)N_TESTES;
        nTrocas += numeroTrocasTotal/(double)N_TESTES;
        numeroTrocasTotal = 0;
        
        clock_gettime(CLOCK_REALTIME, &end);
        elapsed_time[i] = 1.e+6 * (double) (end.tv_sec - start.tv_sec) 
                        + 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);
    }
    numeroTrocasTotal = (long)nTrocas;
    
    QuickSortContainer(elapsed_time, N_TESTES, "QC", &nTrocas);
    int tmpMedio = (elapsed_time[N_TESTES/2] + elapsed_time[(N_TESTES/2) - 1])/2;
    
    printf("%s %s %d %.0lf %ld %d\n", tipoOrdenacao, organizacaoVetor, tamanho,comparacoesTotais, numeroTrocasTotal, tmpMedio);

    if (imprimirArray == 1) {
        for (i = 0; i < N_TESTES; i++) {
            imprime(A[i], tamanho);
        }
    }

    for (i = 0; i < N_TESTES; i++) {
        free(A[i]);
        if (imprimirArray == 1) { free(B[i]); }
    }
    free(A);
    if (imprimirArray == 1) { free(B); }
    free(elapsed_time);
}