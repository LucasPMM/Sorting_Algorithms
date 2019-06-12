#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes/core.h"

int main(int argc, char const *argv[]){
    srand(time(NULL));
	initSort(argc, argv);
	return 0; 
}
