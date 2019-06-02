#include <stdio.h>
#include <stdlib.h>
#include "includes/funcoes.h"
#include "includes/pilha.h"

int main(int argc, char *argv[]){
	int arr[] = { 12, 11, 13, 5, 6 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 

	// insertionSort(arr, n); 
	QuickSortFunction(arr, 5);
	PrintArray(arr, n); 

	// int arr2[] = {10, 7, 8, 9, 1, 5}; 
	// n = sizeof(arr2)/sizeof(arr2[0]); 
	// quickSort(arr2, 0, n-1); 
	// printf("Sorted array: n"); 
	// printArray(arr2, n); 
	return 0; 
}
