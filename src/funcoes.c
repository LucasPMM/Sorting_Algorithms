#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/funcoes.h"
#include "includes/pilha.h"

int Pivo(int *A, int esq, int dir, int tipo) {
	int primeiro = A[esq];
	int meio = A[(esq + dir) / 2];
	int ultimo = A[dir];
	
	if (tipo == 0) { return meio; }
    else if (tipo == 1) { return primeiro; } 
    else if (tipo == 2) {
		if (primeiro > meio) { int t = primeiro; primeiro = meio; meio = t; }
		if (meio > ultimo) { int t = meio; meio = ultimo; ultimo = t; }
		if (primeiro > meio) { int t = primeiro; primeiro = meio; meio = t; }
		return meio;
	}
}

long InsertionSort (int *arr, int esq, int dir, long *numeroTrocas) { 
	int i, chave, j, numeroComparacoes = 0; 
	for (i = esq; i < dir; i++) { 
		chave = arr[i]; 
		j = i - 1; 

		while (j >= 0) {
			numeroComparacoes ++;
			if (chave >= arr[j]) { break; } 
			arr[j + 1] = arr[j]; 
			(*numeroTrocas)++;
			j = j - 1;
		} 
		arr[j + 1] = chave; 
	}
	return numeroComparacoes;
	// Implementação baseada nos slides da matéria! 
}

int Particao (int esq, int dir, int *i, int *j, int *A, int tipo, long *numeroTrocas) {
	int x, w, numeroComparacoes = 0;
	*i = esq;
	*j = dir;

	// Pivo:
	x = Pivo(A, esq, dir, tipo);
	do {
		while (x > A[*i]) {
			numeroComparacoes++;
			(*i) ++;
		}
		while (x < A[*j]) {
			(*j)--;
			numeroComparacoes++;
		}
		numeroComparacoes += 2;

		if (*i <= *j) {
			w = A[*i];
			A[*i] = A[*j];
			A[*j] = w;

			(*i)++;
			(*j)--;
			(*numeroTrocas)++;
		}
 	} while (*i <= *j);

	return numeroComparacoes;
	// Implementação baseada nos slides da matéria! 
}

long Ordena (int esq, int dir, int *A, int tipo, long *numeroTrocas, int condicaoParada) {
	long int numeroComparacoes = 0;
	int i, j;

	if (!condicaoParada) { // Aplica o quicksort para todo o vetor
		if (tipo == 2 && esq - dir <= 2) { tipo = 0; }
		numeroComparacoes = Particao(esq, dir, &i, &j, A, tipo, numeroTrocas);
		if (esq < j) {
			numeroComparacoes += Ordena(esq, j, A, tipo, numeroTrocas, 0);
		}
		if (i < dir) {
			numeroComparacoes += Ordena(i, dir, A, tipo, numeroTrocas, 0);
		}
	} else { // Aplica o insertionsort após a condição de parada
		if (dir - esq > condicaoParada) {
			if (tipo == 2 && dir - esq <= 2) { tipo = 0; }
			if (dir - esq > 2) { numeroComparacoes = Particao(esq, dir, &i, &j, A, tipo, numeroTrocas); }
			else { numeroComparacoes = Particao(esq, dir, &i, &j, A, tipo, numeroTrocas); }

			numeroComparacoes += Ordena(esq, j, A, tipo, numeroTrocas, condicaoParada);
			numeroComparacoes += Ordena(i, dir, A, tipo, numeroTrocas, condicaoParada);
		} else {
			numeroComparacoes = InsertionSort(A, esq, dir + 1, numeroTrocas);
		}
	}

	return numeroComparacoes;
	// Implementação baseada nos slides da matéria! 
}

long QuickSortContainer(int *A, int numeroElementos, char *tipo, long *numeroTrocas) {
    long int numeroComparacoes = 0;
    if (!strcmp(tipo, "QC")) {
        numeroComparacoes = Ordena(0, numeroElementos-1, A, 0, numeroTrocas, 0);
    } else if (!strcmp(tipo, "QM3")) {
        numeroComparacoes = Ordena(0, numeroElementos-1, A, 2, numeroTrocas, 0);
    } else if(!strcmp(tipo, "QPE")) {
        numeroComparacoes = Ordena(0, numeroElementos-1, A, 1, numeroTrocas, 0);
    } else if(!strcmp(tipo, "QI1")) {
        numeroComparacoes = Ordena(0, numeroElementos-1, A, 2, numeroTrocas, numeroElementos/100);
    } else if(!strcmp(tipo, "QI5")) {
        numeroComparacoes = Ordena(0, numeroElementos-1, A, 2, numeroTrocas, numeroElementos/20);
    } else if(!strcmp(tipo, "QI10")) {
        numeroComparacoes = Ordena(0, numeroElementos-1, A, 2, numeroTrocas, numeroElementos/10);
    } else if(!strcmp(tipo, "QNR")){
        numeroComparacoes = QuickSortNaoRec(A, numeroElementos, numeroTrocas);
    }
    return numeroComparacoes;
}

long QuickSortNaoRec (int *A, int tamanho, long *numeroTrocas) {
    int esq = 0, dir = tamanho - 1, i, j;
    long numeroComparacoes = 0;
    Pilha p;
    Item item;
 
    FPVazia(&p);

    item.dir = dir;
    item.esq = esq;

    Empilha(item, &p);
    do {
        if (dir > esq) {
            numeroComparacoes += Particao(esq, dir, &i, &j, A, 0, numeroTrocas);
            if (j - esq > dir - i) {
                item.dir = j;
                item.esq = esq;
                Empilha(item, &p);
                esq = i;
            }
            else {
                item.esq = i;
                item.dir = dir;
                Empilha(item, &p);
                dir = j;
            }
        }
        else {
            Desempilha(&p, &item);
            dir = item.dir;
            esq = item.esq;
        }
    } while (!Vazia(&p));

    return numeroComparacoes;
	// Implementação baseada nos slides da matéria! 
}

// As funções possuem retorno pois devem retornar o tempo de execução!