all: src/main.o src/functions.o
	gcc src/functions.o src/main.o -o sort
	make clean
	clear

functions.o:
	gcc -c src/functions.c

main.o: src/main.c
	gcc -c src/main.c

clean:
	rm src/*.o
