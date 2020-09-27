output: main.o
	gcc -o output main.o

main.o: main.c utilidades/juego.h utilidades/sistema.h utilidades/string++.h
	gcc -c main.c

clear:
	rm -f output *.o