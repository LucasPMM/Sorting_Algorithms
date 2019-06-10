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
		// Realização da mediana de 3
		if (primeiro > meio) { int t = primeiro; primeiro = meio; meio = t; }
		if (meio > ultimo) { int t = meio; meio = ultimo; ultimo = t; }
		if (primeiro > meio) { int t = primeiro; primeiro = meio; meio = t; }
		return meio;
	}
}

long InsertionSort (int *arr, int esq, int dir, long *numeroTrocas) { 
	int i, chave, j, numeroComparacoes = 0; 
	for (i = esq; i <= dir; i++) { 
		chave = arr[i]; 
		j = i - 1; 

		while (j >= 0) {
			numeroComparacoes ++;
			if (chave >= arr[j]) { break; } 
			arr[j + 1] = arr[j]; 
			(*numeroTrocas)++;
			j--;
		} 
		arr[j + 1] = chave;
		(*numeroTrocas)++;
	}
	return numeroComparacoes;
	// Implementação baseada nos slides da matéria! 
}

int Particao (int esq, int dir, int *i, int *j, int *A, int tipo, long *numeroTrocas) {
	int x, w, numeroComparacoes = 0;
	*i = esq;
	*j = dir;

	// seleciona o pivô de acordo com o tipo
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
		// Os dois while acima deixam de incrementar uma vez em seu ultimo loop
		numeroComparacoes += 2;

		if (*i <= *j) {
			// Troca um elemento com outro
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
	// Se não for long int dá valores negativos!?
	long int numeroComparacoes = 0;
	int i, j;

	if (condicaoParada == 0) { // Aplica o quicksort para todo o vetor
		if (tipo == 2 && esq - dir <= 2) { tipo = 0; }
		numeroComparacoes = Particao(esq, dir, &i, &j, A, tipo, numeroTrocas);
		if (esq < j) {
			numeroComparacoes += Ordena(esq, j, A, tipo, numeroTrocas, condicaoParada);
		}
		if (i < dir) {
			numeroComparacoes += Ordena(i, dir, A, tipo, numeroTrocas, condicaoParada);
		}
	} else { // Aplica o insertionsort após a condição de parada
		if (dir - esq > condicaoParada) {
			if (tipo == 2 && dir - esq <= 2) { tipo = 0; }
			numeroComparacoes = Particao(esq, dir, &i, &j, A, tipo, numeroTrocas);
			numeroComparacoes += Ordena(esq, j, A, tipo, numeroTrocas, condicaoParada);
			numeroComparacoes += Ordena(i, dir, A, tipo, numeroTrocas, condicaoParada);
		} else {
			numeroComparacoes = InsertionSort(A, esq, dir, numeroTrocas);
		}
	}

	return numeroComparacoes;
	// Implementação baseada nos slides da matéria! 
}

long QuickSortContainer(int *A, int numeroElementos, char *tipo, long *numeroTrocas) {
    long int numeroComparacoes = 0;
	// Interface que coordena os argumentos a serem enviados para a função Ordena
	// levando em consideração o tipo de quicksort

	// Em relação a forma de escolha de pivo, a seguinte regra é respeitada:
	// tipo = 0	=> 'Pivo = Elemento Central'
	// tipo = 1	=> 'Pivo = Primeiro Elemento'
	// tipo = 2	=> 'Pivo = Mediana de Três'

	int insercao1 = numeroElementos / 100;
	int insercao5 = numeroElementos / 20;
	int insercao10 = numeroElementos / 10;

    if (!strcmp(tipo, "QC")) {
        numeroComparacoes = Ordena(0, numeroElementos, A, 0, numeroTrocas, 0);
    } else if (!strcmp(tipo, "QM3")) {
        numeroComparacoes = Ordena(0, numeroElementos, A, 2, numeroTrocas, 0);
    } else if(!strcmp(tipo, "QPE")) {
        numeroComparacoes = Ordena(0, numeroElementos, A, 1, numeroTrocas, 0);
    } else if(!strcmp(tipo, "QI1")) {
        numeroComparacoes = Ordena(0, numeroElementos, A, 2, numeroTrocas, insercao1);
    } else if(!strcmp(tipo, "QI5")) {
        numeroComparacoes = Ordena(0, numeroElementos, A, 2, numeroTrocas, insercao5);
    } else if(!strcmp(tipo, "QI10")) {
        numeroComparacoes = Ordena(0, numeroElementos, A, 2, numeroTrocas, insercao10);
    } else if(!strcmp(tipo, "QNR")){
        numeroComparacoes = QuickSortNaoRec(A, numeroElementos, numeroTrocas);
    }
    return numeroComparacoes;
}

// Implementação não recursiva do quicksort
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
