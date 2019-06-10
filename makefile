all: main.o funcoes.o pilha.o utils.o
	gcc -O3 funcoes.o utils.o main.o pilha.o -o sort
	make clean
	clear

funcoes.o: src/funcoes.c src/includes/funcoes.h
	gcc -O3 -c src/funcoes.c

pilha.o: src/pilha.c src/includes/pilha.h
	gcc -O3 -c src/pilha.c

utils.o: src/utils.c src/includes/utils.h
	gcc -O3 -c src/utils.c

main.o: src/main.c
	gcc -O3 -c src/main.c

clean:
	rm *.o
