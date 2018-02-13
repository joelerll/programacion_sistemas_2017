#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "utils.h"

long total = 0;

long aleatorio(long min, long max) {
  long r = rand();
  return (r % (max-min+1)) + min;
}

double obtenerTiempoActual() {
    struct timespec tsp;
    clock_gettime(CLOCK_REALTIME, &tsp);
    double secs = (double)tsp.tv_sec;
    double nano = (double)tsp.tv_nsec / 1000000000.0;
    return secs + nano;
}

/*
    [argumentos]
    arreglo, tamanio;
*/

void *sumar (void *arg) {
    long total = 0;
    infoArreglo *arreglo_estuctura = (infoArreglo*) arg;
    long *inicio = arreglo_estuctura->inicio;
    fseek(stdin,0,SEEK_END);
    for (long i = 0; i < arreglo_estuctura->tamano; i++) {
        total = total + *(inicio + i);
    }
    //printf("%li+ %li = %li\n",tmp,*(inicio + i),total);
    return (void *)total;
}

long *generarArreglo (long tamano) {
    long *arreglo = malloc(sizeof(long) * tamano);
    for(long i = 0; i < tamano; i++) {
        arreglo[i] = aleatorio(0,100);
    }

	/*for(long j=0 ; j<tamano ; j++ ){
		printf("%li\n",*(arreglo+j));
	}*/

    return arreglo;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    // variables globales
    long *arreglo_generado;
    infoArreglo **arreglo_particionado;
    long status;
    double inicio,fin;
    void *tmp;

    // TODO: validar
    if(argc!=3){
        printf("\n**Error, argumentos invalidos, vuelva a intentarlo**\n\n");
        return 0;
    }

    long tamano_arreglo = atoi(argv[1]);
    long numero_hilos = atoi(argv[2]);


    if(tamano_arreglo==0 || numero_hilos==0) {
        printf("\n**Error al ingresar argumentos, vuelva a intentarlo**\n\n");
        return 0;
    }

    pthread_t hilos[16] = {0};

    arreglo_generado = generarArreglo(tamano_arreglo);

    arreglo_particionado = funcionDivInfo(arreglo_generado,tamano_arreglo,numero_hilos); // TODO: BOSCO

    inicio = obtenerTiempoActual();

    for(size_t i = 0; i < numero_hilos; i++) {
        fseek(stdin,0,SEEK_END);
        status = pthread_create(&hilos[i], NULL, sumar, (void *)*(arreglo_particionado + i));
        if (status < 0) {
            fprintf(stderr, "Error al crear el hilo\n");
            exit(-1);
        }
    }

    for (size_t k = 0; k < numero_hilos; k++) {
      pthread_join(hilos[k], &tmp);
      total = total + (long)tmp;
    }

    fin = obtenerTiempoActual();
    printf("%li %f %li",numero_hilos,fin-inicio, total);

    //500000000
    //FILE * archivoPuntos = fopen("puntosGraficar.txt", "w");
    //fprintf(archivoPuntos, "%li %f \n", numero_hilos, fin-inicio);
    //fclose(archivoPuntos);

    return 0;
}
