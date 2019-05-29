#include <stdio.h>
#include <stdlib.h>
#include "includes/functions.h"

void InsertionSort (int *arr, int n) { 
	int i, key, j; 
	for (i = 1; i < n; i++) { 
		key = arr[i]; 
		j = i - 1; 

		while (j >= 0 && arr[j] > key) { 
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1] = key; 
	} 
} 

void PrintArray (int *arr, int n)  { 
	int i; 
	for (i = 0; i < n; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

void Partition (int Esq, int Dir, int *i, int *j, int *A) {
	int x, w;
	*i = Esq;
	*j = Dir;

	// Pivo:
	x = A[((*i + *j) / 2)];
	do {
		while (x > A[*i]) (*i)++;
		while (x < A[*j]) (*j)--;

		if (*i <= *j) {
			w = A[*i];
			A[*i] = A[*j];
			A[*j] = w;

			(*i)++;
			(*j)--;
		}
 	} while (*i <= *j);
}

void Order (int Esq, int Dir, int *A) {
	int i, j;

	Partition(Esq, Dir, &i, &j, A);
	if (Esq < j) Order(Esq, j, A);
	if (i < Dir) Order(i, Dir, A);
}

void QuickSortFunction (int *A, int n) {
	Order(0, n-1, A);
}