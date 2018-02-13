#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

//Estructura válida para almacenar información respecto 
//a la subparte del arreglo de enteros que va a manejar cada hilo
infoArreglo ** funcionDivInfo(long *arraylong, long lenArray, long nHilos){

	infoArreglo **arrayInfoArreglo = malloc(sizeof(infoArreglo*));
	infoArreglo *info;
	long nSubPartes = lenArray/nHilos;
	long contador=0;
	
	fseek(stdin,0,SEEK_END);
	
	for(int i=0;i<lenArray;i=i+nSubPartes){

		if(i+nSubPartes>lenArray){
			info->tamano = lenArray - ((nHilos-1)*(info->tamano));
			i=lenArray;
		}else{
			info = malloc(sizeof(infoArreglo));	
			info->inicio = arraylong + i;
			info->tamano = nSubPartes;
			*(arrayInfoArreglo+contador) = info;
			contador++;

		}		
	}

	/*for(long z=0 ; z<nHilos ; z++){
		infoArreglo *info1 = *(arrayInfoArreglo+z);
		printf("\n\nInicio: %ld, Tamano: %ld\n",*(info1->inicio),(info1->tamano));
	}*/
	
	return arrayInfoArreglo; 
}