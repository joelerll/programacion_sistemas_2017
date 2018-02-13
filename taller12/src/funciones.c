#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000000

//retorna numero_lineas -1
int numero_lineas(char *ruta, int *tam_lineas){
    if(ruta != NULL){
        FILE * ar = fopen(ruta,"r");
        int lineas = 0;
        int tam_linea;
        while(!feof(ar)){
            tam_linea++;
            char c = getc(ar);
            if( c == '\n'){
                if( tam_lineas != NULL ){
                    tam_lineas[lineas] = tam_linea;
                }
                lineas ++;
                tam_linea = 0;
            }
        }
        fclose(ar);
        return lineas;
    }
    return -1;
}

char** recolectarPalabras(int nPalabras, char **argv){
    
    char ** palabrasABuscar = malloc(nPalabras*sizeof(char*));

    for( int i=0 ; i<nPalabras ; i++){
        *(palabrasABuscar+i) = argv[3+i];
    }

    return palabrasABuscar;

}

//Función que divide archivo en n partes de igual tamano
char** dividirArchivo(char *ruta, int partes, int tamano){

    int ubicacion = 0;
    char **archivoDividido = malloc(partes*sizeof(char*));

    for( int i=0 ; i<partes ; i++){
        
        FILE * ar = fopen(ruta,"r");
        fseek(ar,ubicacion,SEEK_SET); 
        *(archivoDividido+i) = malloc(tamano*sizeof(char));

        for( int j=0 ; j<tamano ; j++){
            char c = getc(ar);
            *(*(archivoDividido+i)+j) = c;    
        }

        //printf("%s\n\n",*(archivoDividido+i));        
        ubicacion = ubicacion + tamano;

    }

    return archivoDividido;

}

int getTotalCaracteresArchivo(int numLineas, int *numCaracteresXLinea){

    int totalCaracteres = 0;

    for( int i=0 ; i<numLineas ; i++){
        totalCaracteres = totalCaracteres + *(numCaracteresXLinea+i);
    }

    return totalCaracteres;
}

void contarOcurrencias(char **palabrasABuscar, char *texto, int *numOcurrencias, int numPalabrasABuscar){

    char *token ;
    
    token = strtok(texto," ,.!?:;");

    while( token != NULL ){
        
        for( int i=0 ; i<numPalabrasABuscar ; i++){
            
            if( !strcmp( *(palabrasABuscar+i), token ) ){
                *(numOcurrencias+i) += 1;    
            }
                

        }
        
        token = strtok(NULL," ,.!?:;\n");
        
    }

}


