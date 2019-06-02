all: src/main.o src/funcoes.o
	gcc src/funcoes.o src/main.o src/pilha.o -o sort
	make clean
	clear

funcoes.o:
	gcc -c src/funcoes.c

pilha.o:
	gcc -c src/pilha.c

main.o: src/main.c
	gcc -c src/main.c

clean:
	rm src/*.o
