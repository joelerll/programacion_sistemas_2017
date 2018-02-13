all: taller

taller: taller.o funciones.o
	gcc  -pthread obj/funciones.o obj/taller.o -o bin/hilos

funciones.o: src/funciones.c
	gcc -c -Wall  -Iinclude/ src/funciones.c -o obj/funciones.o

taller.o: src/taller.c include/utils.h
	gcc -c -Wall -pthread -Iinclude/ src/taller.c -o obj/taller.o

.PHONY: all graficar

clean:
	rm -rf bin/* obj/*

graficar: grafica.plt datosHvsT.dat
	gnuplot -persist grafica.plt
