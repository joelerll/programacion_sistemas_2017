#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "utils.h"

void *ocurrencias (void *arg);
void imprimir();

pthread_mutex_t mutex;
int *numOcurrencias;
char **palabrasABuscar;
int nPalabrasABuscar;
int contador=0;

int main(int argc, char **argv) {

    //Ruta del archivo
    char *ruta = argv[1];
    //Número de hilos que ejecutaŕa el programa
    int nHilos = atoi(argv[2]);
    //Cantidad de palabras que van a ser buscadas
    nPalabrasABuscar = argc-3;
    //Asginar en arreglo palabras que serán buscadas
    palabrasABuscar = recolectarPalabras(argc-3,argv);
    //Número de líneas que contiene el archivo
    int numLineas = numero_lineas(ruta,NULL);
    //Número de caracteres que contiene cada línea
    int *numCaracteresXLinea = malloc(numLineas*sizeof(int));
    numero_lineas(ruta,numCaracteresXLinea);
    //Total de caracteres que contiene el archivo
    int totalCaracteres = getTotalCaracteresArchivo(numLineas,numCaracteresXLinea);
    //Tamaño de partes en que se dividirá el archivo
    int tamanoParticion = totalCaracteres / nHilos;
    //Archivo dividido
    char **archivoDividido = dividirArchivo(ruta,nHilos,tamanoParticion);
    //Inicialización de puntero numOcurrencias
    numOcurrencias = malloc(nPalabrasABuscar*sizeof(int));

    for( int i=0 ; i<nPalabrasABuscar ; i++){
        *(numOcurrencias+i) = 0;
    }

    pthread_t *hilos = malloc( nHilos * sizeof(pthread_t));

    //Creación de mutex
    pthread_mutex_init(&mutex,NULL);

    //Ejecución de hilos
    for( int i = 0; i < nHilos ; i++ ) {
        int status = pthread_create(hilos+i, NULL, ocurrencias, (void *)*(archivoDividido+i));
        if (status < 0) {
            fprintf(stderr, "Error al crear el hilo\n");
            exit(-1);
        }
        pthread_join(*(hilos+i),NULL);
    }

    return 0;

}

void *ocurrencias (void *arg) {

    char *texto = (char*) arg;
    
    pthread_mutex_lock(&mutex);

    for( int i = 0; i < nPalabrasABuscar ; i++ ) 
        contarOcurrencias(palabrasABuscar,texto,numOcurrencias,nPalabrasABuscar);

    imprimir();
    pthread_mutex_unlock(&mutex);
    
    return (void *) 0;

}

void imprimir(){
    contador += 1;
    printf("-------------------------------------------------%i\n",contador);
    for( int i = 0; i < nPalabrasABuscar ; i++ ) {
        printf("Palabra: %s - Ocurrencias: %i\n",*(palabrasABuscar+i),*(numOcurrencias+i));
    }
    printf("-------------------------------------------------\n");
}

