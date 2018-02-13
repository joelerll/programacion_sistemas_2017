#include <stdio.h>
void desglosar(char * fecha);
void intercambiar(int *a, int* b);
int* funcion2(int ptr[], int ocurrencia, int tam);
int main(int argc, char const *argv[]) {
  printf("-----------------------------\n");
  char* fecha = "2017-06-06";
  desglosar(fecha);

  int numero[4];
	numero[0]=1;
	numero[1]=2;
	numero[2]=3;
	numero[3]=6;
  printf("-----------------------------\n");
	int *memoria = funcion2(numero,1,4);
	printf("Dirección de memoria: %p\n",memoria);


  int a = 2;
  int b = 3;
  intercambiar(&a, &b);
  printf("\n-----------------------------\n");
  printf("%d\n", a);
  printf("%d\n", b);

  return 0;
}

void desglosar(char* fecha) {
  int cont = 0;
  char tmp[50];
  int cont_tmp = 0;
  int cont_array = 0;
  char *dia[] = {"años","mes", "dia"};
  while (fecha[cont] != '\0') {
    cont++;
  }
  for (size_t i = 0; i < cont; i++) {
    if (fecha[i] == '-') {
      tmp[cont_tmp] = '\0';
      printf("%s: %s\n", dia[cont_array], tmp);
      cont_tmp = 0;
      cont_array++;
      // *tmp = '';
    } else {
      tmp[cont_tmp] = fecha[i];
      cont_tmp++;
      if (fecha[i+1] == '\0') {
        printf("%s: %s\n", dia[cont_array], tmp);
      }
    }
  }
}

void intercambiar(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int* funcion2(int ptr[], int ocurrencia, int tam){

	int i;
	for(i=0;i<tam;i++){
		if(ptr[i]==ocurrencia){
			return &ptr[i];
		}
	}

	return NULL;

}
