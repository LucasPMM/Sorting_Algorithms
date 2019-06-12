#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "includes/core.h"
#include "includes/utils.h"
#include "includes/funcoes.h"

// "Variavel global" que determina o número de vetores a serem gerados
// com o intuito de obter as médias e mediana necessárias
#define N_TESTES 20

// Função 'cabeça' do programa:
int initSort (int argc, char *argv[]) {
    struct timespec start, end;
    int *elapsed_time;
    double comparacoesTotais = 0.0, nTrocas = 0.0;
    long numeroTrocasTotal = 0;
    int **A, **B, i, j, tamanho, imprimirArray = 0, tmpMedio = 0;
    char *tipoOrdenacao;    // QC | QM3 | QPE | QI1 | QI5 | QI10 | QNR
    char *organizacaoVetor; // OrdC | OrdD | Ale

    // Pegando os argumentos de função do argv:
    tipoOrdenacao = (char*) malloc(5 * sizeof(char));
    organizacaoVetor = (char*) malloc(5 * sizeof(char));
    tamanho = atoi(argv[3]);
    strcpy(tipoOrdenacao, argv[1]);
    strcpy(organizacaoVetor, argv[2]);

    elapsed_time = (int*) malloc(N_TESTES * sizeof(int));

    // Gerando N_TESTES arrays para pegar a mediana de tempo
    if (strcmp(organizacaoVetor, "OrdC") == 0) { A = geraArrayCrescente(tamanho); }
    if (strcmp(organizacaoVetor, "OrdD") == 0) { A = geraArrayDecrescente(tamanho); }
    if (strcmp(organizacaoVetor, "Ale") == 0) {  A = geraArrayAleatorio(tamanho); }

    // Caso seja necessário imprimir os arrays no final, realizamos 
    // uma cópia antes da ordenação para que a sua forma original não seja perdida.  
    if (argc == 5 && strcmp(argv[4], "-p") == 0) {
        imprimirArray = 1;
        B = (int**) malloc(N_TESTES * sizeof(int*));
        for (i = 0; i < N_TESTES; i++) {
            B[i] = (int*) malloc(tamanho * sizeof(int));
            for (j = 0; j < tamanho; j++) {
                B[i][j] = A[i][j];
            }
        }
    } // Extrair para um método de cópia seria uma possível melhoria

    // Implementação do calculo de tempo seguindo a documentação disponibilizada no Apendice da descrição do trabalho
    for (i = 0; i < N_TESTES; i++) {
        clock_gettime(CLOCK_REALTIME, &start);
        comparacoesTotais += QuickSortContainer(A[i], tamanho - 1, tipoOrdenacao, &numeroTrocasTotal)/(double)N_TESTES;        
        nTrocas += numeroTrocasTotal/(double)N_TESTES;
        numeroTrocasTotal = 0;
        clock_gettime(CLOCK_REALTIME, &end);
        elapsed_time[i] = 1.e+6 * (double) (end.tv_sec - start.tv_sec) + 1.e-3 * (double) (end.tv_nsec - start.tv_nsec);
    }
    
    // Ordenando o vetor de tempos de execução para que possamos pegar a mediana do tempo:
    numeroTrocasTotal = (long)nTrocas;
    // long aux_nTrocas = (long)nTrocas;
    QuickSortContainer(elapsed_time, N_TESTES, "QC", &nTrocas);
    tmpMedio = (elapsed_time[N_TESTES/2] + elapsed_time[(N_TESTES/2) - 1])/2;
    
    // Impressões de resultados
    printf("%s ", tipoOrdenacao);       // QC | QM3 | QPE | QI1 | QI5 | QI10 | QNR
    printf("%s ", organizacaoVetor);    // OrdC | OrdD | Ale
    printf("%d ", tamanho);             // 50000 | 100000 | 150000 | 200000 | 250000 | 300000 | 350000 | 400000 | 450000 | 500000
    printf("%.0lf ", comparacoesTotais);
    printf("%ld ", numeroTrocasTotal);
    printf("%d\n", tmpMedio);

    // Imprimir o vertor utilizado caso tenha entrado com '-p'
    if (imprimirArray == 1) {
        for (i = 0; i < N_TESTES; i++) {
            imprime(B[i], tamanho);
        }
    }

    // Liberar a memória alocada 
    // (Extrair para um método libera seria uma possível melhoria)
    for (i = 0; i < N_TESTES; i++) {
        free(A[i]);
        if (imprimirArray == 1) { free(B[i]); }
    }
    free(A);
    if (imprimirArray == 1) { free(B); }
    free(elapsed_time);
}