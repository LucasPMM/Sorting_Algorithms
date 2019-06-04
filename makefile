all: src/main.o src/funcoes.o src/pilha.o src/utils.o
	gcc src/funcoes.o src/utils.o src/main.o src/pilha.o -o sort
	make clean
	clear

funcoes.o:
	gcc -c src/funcoes.c

pilha.o:
	gcc -c src/pilha.c

utils.o:
	gcc -c src/utils.c

main.o: src/main.c
	gcc -c src/main.c

clean:
	rm src/*.o
