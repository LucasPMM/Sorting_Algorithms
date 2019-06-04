#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes/utils.h"

int main(int argc, char *argv[]){
    srand(time(NULL));
	initSort(argc, argv);
	return 0; 
}
