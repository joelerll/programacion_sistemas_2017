#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codificacion.h"
#include "cifrado.h"

void imprimirMenu();
void imprimirMenuArgumentos(char *argumentos[]);
int esNumero(char num[]);
int esString(char string[]);
int esComando(char *comando);
int main(int arg, char *argv[]){


	switch(arg){

		case 1:
			imprimirMenu();
			break;

		case 4:						

			if(esComando(argv[3])){
				imprimirMenuArgumentos(argv);
			} else {
				printf("\n\n***********************************************************************************************\n\n");
				printf("\tError: comando invalido");
				printf("\n\n***********************************************************************************************\n\n");
			}

			break;

		default:
			printf("\n\n***********************************************************************************************\n\n");
			printf("\tError: faltan argumentos");
			printf("\n\n***********************************************************************************************\n\n");
	}

	return 0;

}

void clean_stdin(void) {
	int c;
   	do {
	     c = getchar();
	}while (c != '\n' && c != EOF);
}


void imprimirMenu(){

        char mensaje[1000], llave[1000], cifrado[1000];

        printf("\n\n***********************************************************************************************\n\n");
	printf("\tTipo de cifrado: ");
	scanf("%[^\n]",cifrado);

	switch(cifrado[0]){

		case 'C':
			printf("\tCifrado ciclico\n");
			printf("\tIngrese mensaje a cifrar     : ");
			clean_stdin();
			fgets(mensaje, sizeof(mensaje), stdin);
			printf("\tIngrese la llave numerica    : ");
			scanf("%s",llave);
			if(esNumero(llave)){
				cifradoCiclico(mensaje,atoi(llave));
				printf("\tMensaje cifrado              : %s",mensaje);
				printf("\tMensaje cifrado en morse     : ");
				claveMorse(mensaje);
			}else{
				printf("\tError: llave invalida");
			}
			break;

		case 'A':
			printf("\tCifrado autollave\n");
			printf("\tIngrese mensaje a cifrar     : ");
			clean_stdin();
			fgets(mensaje, sizeof(mensaje), stdin);
			printf("\tIngrese la llave             : ");
			scanf("%[^\n]",llave);
			if(esString(llave)){						
				cifradoAutollave(mensaje,llave);
				printf("\tMensaje cifrado              : %s",mensaje);
			}else{
				printf("\tError: llave invalida");
			}
			break;

		case 'P':
			printf("\tCifrado contraseña\n");
			printf("\tIngrese mensaje a cifrar     : ");
			clean_stdin();
			fgets(mensaje, sizeof(mensaje), stdin);
			printf("\tIngrese la llave             : ");
			scanf("%[^\n]",llave);
			cifradoContrasena(mensaje,llave);
			printf("\tMensaje cifrado              : %s",mensaje);
			break;

		default:
			printf("\tError: comando invalido");

	}

        printf("\n\n***********************************************************************************************\n\n");
}

void imprimirMenuArgumentos(char *argumentos[]){

	printf("\n\n***********************************************************************************************\n\n");
	char *comando=argumentos[3];

	switch(comando[1]){

		case 'c':

			if(esNumero(argumentos[1])){
				printf("\tTipo de cifrado: C");
				printf("\n\tCifrado ciclico\n");
				printf("\tIngrese mensaje a cifrar     : %s\n",argumentos[2]);
				printf("\tIngrese la llave numerica    : %s\n",argumentos[1]);
				cifradoCiclico(argumentos[2],atoi(argumentos[1]));
				printf("\tMensaje cifrado              : %s",argumentos[2]);
				printf("\n\tMensaje cifrado en morse    : ");
				claveMorse(argumentos[2]);
			}else{
				printf("\tError: llave invalida");
			}
			break;

		case 'a':

			if(esString(argumentos[1])){
				printf("\tTipo de cifrado: A\n");
				printf("\tCifrado autollave\n");
				printf("\tIngrese mensaje a cifrar     : %s\n",argumentos[2]);
				printf("\tIngrese la llave             : %s\n",argumentos[1]);
				cifradoAutollave(argumentos[2],argumentos[1]);
				printf("\tMensaje cifrado              : %s",argumentos[2]);
			}else{
				printf("\tError: llave invalida");
			}
					
			break;

		case 'p':

			printf("\tTipo de cifrado: P\n");
			printf("\tCifrado contraseña\n");
			printf("\tIngrese mensaje a cifrar     : %s\n",argumentos[2]);
			printf("\tIngrese la llave             : %s\n",argumentos[1]);
			cifradoContrasena(argumentos[2],argumentos[1]);
			printf("\tMensaje cifrado              : %s",argumentos[2]);
			break;

		default:
			printf("\tError: comando invalido");

	}

	printf("\n\n***********************************************************************************************\n\n");

}

int esComando(char *comando){

	if(!(*comando=='-')){
		return 0;
	}else if(*(comando+1)=='c'||*(comando+1)=='a'||*(comando+1)=='p'){
		if(*(comando+2)=='\0')
			return 1;
	}
	return 0;

}

int esNumero(char num[]){

        int i;

	if((num[0]==45&&num[1]=='\0') || (num[0]==43&&num[1]=='\0'))
		return 0;

        for(i=1;num[i]!='\0';i++){
                if(!(num[i]>=48 && num[i]<=57)){
                        return 0;
                }
        }
        return 1;
}

int esString(char string[]){

        int i;

        for(i=0;string[i]!='\0';i++){
                if(!((string[i]>=97 && string[i]<=122) || (string[i]>=65 && string[i]<=90) || string[i]==32)){
                        return 0;
                }
        }
        return 1;
}

