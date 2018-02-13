#include <stdio.h>
#include <string.h>

char *claveMorse(char *mensaje){

	char *codigoMorse[]={" .-"," -..."," -.-."," -.."," ."," ..-."," --."," ...."," .."," .---"," -.-"," .-.."," --"," -."," ---"
                                ," .--."," --.-"," .-."," ..."," -"," ..-"," ...-"," .--"," -..-"," -.--"," --.."," -----"," .----"," ..---"
                                ," ...--"," ....-"," ....."," -...."," --..."," ---.."," ----."," /"};
	int i;

	for(i=0;*(mensaje+i)!='\0';i++){

	        if(*(mensaje+i)>=48 && *(mensaje+i)<=57){
			printf("%s",codigoMorse[0]);

		}else if(*(mensaje+i)==32){
			printf("%s",codigoMorse[36]);

		}else if(*(mensaje+i)>=65&&*(mensaje+i)<=90){
			printf("%s",codigoMorse[*(mensaje+i)-65]);
	
		}else if(*(mensaje+i)>=97&&*(mensaje+i)<=122){
			printf("%s",codigoMorse[*(mensaje+i)-97]);

		}else{
			printf("%c",*(mensaje+i));

		}
	}

	return mensaje;

}

