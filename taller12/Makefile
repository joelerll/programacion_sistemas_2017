all: taller12

taller12: taller12.o funciones.o
	gcc  -pthread obj/funciones.o obj/taller12.o -o bin/buscar

funciones.o: src/funciones.c
	gcc -c -Wall  -Iinclude/ src/funciones.c -o obj/funciones.o

taller12.o: src/taller12.c include/utils.h
	gcc -c -Wall -pthread -Iinclude/ src/taller12.c -o obj/taller12.o

.PHONY: all

clean:
	rm -rf bin/* obj/*
