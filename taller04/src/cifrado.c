#include "cifrado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// incio cifrado ciclico
int nuevoValor(int min, int max, int pos, int desfase){
        int i;
        if(desfase>0){

                for (i=1;i<=desfase;i++){
                        if(pos<max){
                                pos=pos+1;
                        }else{
                                pos=min;
                        }
                }
         }else{
                for (i=1;i<=(desfase*-1);i++){
                        if(pos>min){
                                pos=pos-1;
                        }else{
                                pos=max;
                        }
                }

         }
        return pos;
}

char *cifradoCiclico(char *mensaje, int llave){

        int i;

        for(i=0;*(mensaje+i)!='\0';i++){

                if(*(mensaje+i)>=65 && *(mensaje+i)<=90){
                        *(mensaje+i)=nuevoValor(65,90,*(mensaje+i),llave);
                }else{
                        if(*(mensaje+i)>=97 && *(mensaje+i)<=122)
                                *(mensaje+i)=nuevoValor(97,122,*(mensaje+i),llave);
                }
        }

	return mensaje;

}

// inicio cifrado autollave
char *cifradoAutollave(char *mensaje,char *llave){
	int k = 0;
	const char *str1 = llave;
	const char *str2 = mensaje;
	char *pass = malloc(strlen(str1) + strlen(str2) + 1);
	while(*str1){
		pass[k++]=*str1++;
	}
  	while(*str2){
      		pass[k++]=*str2++;
  	}
  	pass[k]='\0';

	char *tmp;
  	while((tmp=strchr(pass,' '))!=NULL){
		strcpy(tmp,tmp+1);
  	}

	int i,j=0;
    	for(i=0;i<strlen(mensaje);i++){
		if (mensaje[i]!=32){
			if ((mensaje[i]>=65&&mensaje[i]<=90) && (pass[j]>=65&&pass[j]<=90)){
				mensaje[i]=((mensaje[i]+pass[j])%26)+65;
			}else if ((mensaje[i]>=97&&mensaje[i]<=122) && (pass[j]>=97&&pass[j]<=122)){
				mensaje[i]=(((mensaje[i]+pass[j])-64)%26)+97;
			}else if ((mensaje[i]>=97&&mensaje[i]<=122) && (pass[j]>=65&&pass[j]<=90)){
				mensaje[i]=(((mensaje[i]-32)+pass[j])%26)+97;
			}else if ((mensaje[i]>=65&&mensaje[i]<=90) && (pass[j]>=97&&pass[j]<=122)){
				mensaje[i]=((mensaje[i]+(pass[j]-32))%26)+65;
			}
			j=j+1;
		}
    	}
    	return mensaje;
}
// fin cifrado autollave

// inicio cifrado contrasena

char *cifradoContrasena(char *mensaje, char *llave){
	int k = 0;
	const char *str1 = llave;
	const char *str2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("\tAlfabeto                     : %s\n", str2);
	char *tmp;
  	while((tmp=strchr(llave,' '))!=NULL){
		strcpy(tmp,tmp+1);
  	}

	char *pass = malloc(strlen(str1) + strlen(str2) + 1);
	while(*str1){
		pass[k++]=*str1++;
	}
  	while(*str2){
      		pass[k++]=*str2++;
  	}
  	pass[k]='\0';
	printf("\tNuevo Alfabeto               : %s\n", pass);
	int i;
	for(i=0;i<strlen(mensaje);i++){
		if (mensaje[i]!=32){
			if ((mensaje[i]>=65&&mensaje[i]<=90)){
				mensaje[i]=pass[mensaje[i]-65];
			}else if (mensaje[i]>=97&&mensaje[i]<=122){
				mensaje[i]=pass[mensaje[i]-97];
			}
		}
    	}
    	return mensaje;
}

// fin cifrado contrasena