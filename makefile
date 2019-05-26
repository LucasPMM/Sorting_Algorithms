all: src/codigo.o
	gcc src/codigo.o -o sort
	make clean
	clear

codigo.o:
	gcc -c src/codigo.c

main.o: src/codigo.c
	gcc -c src/codigo.c

clean:
	rm src/*.o