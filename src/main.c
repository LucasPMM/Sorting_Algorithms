#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "includes/utils.h"

int main(int argc, char const *argv[]){
    srand(time(NULL));
	initSort(argc, argv);
	return 0; 
}
