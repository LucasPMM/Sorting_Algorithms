int Pivo(int *A, int esq, int dir, int tipo);
long InsertionSort (int *arr, int esq, int dir, long *numeroTrocas);
int Particao (int esq, int dir, int *i, int *j, int *A, int tipo, long *numeroTrocas);
long Ordena (int esq, int dir, int *A, int tipo, long *numeroTrocas, int condicaoParada);
// tipo = 0	=> 'Pivo = Elemento Central'
// tipo = 1	=> 'Pivo = Primeiro Elemento'
// tipo = 2	=> 'Pivo = Mediana de Três'
long QuickSortContainer(int *A, int numeroElementos, char *tipo, long *numeroTrocas);
long QuickSortNaoRec (int *A, int tamanho, long *swap);