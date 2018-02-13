#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void clean_stdin(void);
void morse(char letra);
int main(int argc, char const *argv[]) {
  char mensaje[80] = {0};
  int llave = 0;
  int c;
  bool string_no_valido = false;
  bool numero_no_valido = false;
  if (argc == 3) {
    llave = strtol(argv[1], NULL, 10);
    for (int i = 0; i < sizeof(argv[2]); i++) {
      mensaje[i] = argv[2][i];
      if (argv[2][i] == '\0') {
        break;
      }
    }
    for (int i = 0; i < sizeof(mensaje); i++) {
      c = (int)mensaje[i];
      if (mensaje[i] == '\n') {
        break;
      }
      if ( (c < 65 || ( c > 90 && c < 97 ) || c > 122 ) &&  c!=10 && c!= 0 && c!= 32 && c!= -1  && c!= 47) {
        string_no_valido = true;
        break;
      } else {
        string_no_valido = false;
      }
    }
    if ( llave == 0 ) {
      numero_no_valido = true;
    }
    if (numero_no_valido) {
      printf("\n!!!!Numero no valido \n");
      return 0;
    }
    if (string_no_valido) {
      printf("\n!!!!String no valido \n");
      return 0;
    }
    // printf("%s\n", mensaje);
    // printf("%d\n",llave);
  } else if (argc > 3 || argc == 2) {
    printf("Numero de argumentos no validos");
    return 0;
  } else {
    /* MENU */
    printf("Cifrado ciclico\n");
    do {
      memset(mensaje, 0, sizeof(mensaje));
      if (numero_no_valido) {
        printf("\n!!!!Numero no valido \n");
      }
      numero_no_valido = false;
      if (string_no_valido) {
        printf("\n!!!!String no valido \n");
      }

      printf("Ingrese el mensaje a cifrar: ");
      fgets(mensaje, sizeof(mensaje), stdin);
      for (int i = 0; i < sizeof(mensaje); i++) {
        c = (int)mensaje[i];
        // if (mensaje[i] == '\n') {
        //   break;
        // }
        if ( (c < 65 || ( c > 90 && c < 97 ) || c > 122 ) &&  c!=10 && c!= 0 && c!= 32 && c!= -1 && c!= 47) {
          printf("%d\n",c);
          string_no_valido = true;
          break;
        } else {
          string_no_valido = false;
        }
      }
      printf("Ingrese la llave numerica: ");
      scanf("%d", &llave);
      if ( llave == 0) {
        numero_no_valido = true;
      }
      clean_stdin();
    } while(llave == 0 || (int)mensaje[0] == 10 || string_no_valido == true);
    /* FIN MENU */
  }

  char palabra_codificada[80];
  int letra_movida;
  int limite_sup;
  int limite_inf;
  for (int i = 0; i < sizeof(mensaje); i++) {
    if (mensaje[i] == '\0' || (int)mensaje[i] == 10 || (int)mensaje[i] == 0) {
      palabra_codificada[i] = '\0';
      break;
    }
    if ( (int)mensaje[i] < 91 ) {
      limite_sup = 90;
      limite_inf = 65;
    } else {
      limite_sup = 122;
      limite_inf = 97;
    }
    letra_movida = (int)mensaje[i] + llave;
    if ((int)mensaje[i] != 32) {
      if ( letra_movida > limite_sup ) {
        letra_movida = (letra_movida - limite_sup) + limite_inf;
      }
      if ( letra_movida < limite_inf ) {
        letra_movida = limite_sup - (limite_inf - letra_movida) ;
      }
    } else {
      letra_movida = (int)mensaje[i];
    }
    palabra_codificada[i] = (char)letra_movida;
  }
  printf("Mensaje Cifrado: %s\n", palabra_codificada);
  printf("Mensase morse: ");
  for (int i = 0; i < sizeof(palabra_codificada); i++) {
    if ((int)palabra_codificada[i] == 32) {
      printf(" / ");
    }
    if (palabra_codificada[i] == '\0') {
      break;
    }
    morse(palabra_codificada[i]);
    printf("  ");
  }
  printf("\n");
  return 0;
}

void clean_stdin(void) {
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}


void morse(char letra) {
  int c = (int)letra;
  if (c > 90) {
    c = c - 32;
  }
  if (c == 65) {
    printf(".-");
  } else if (c == 66) {
    printf("-...");
  } else if (c == 67) {
    printf("-.-.");
  } else if (c == 68) {
    printf("-..");
  } else if (c == 69) {
    printf(".");
  } else if (c == 70) {
    printf("..-.");
  } else if (c == 71) {
    printf("--.");
  } else if (c == 72) {
    printf("....");
  } else if (c == 73) {
    printf("..");
  } else if (c == 74) {
    printf(".---");
  } else if (c == 75) {
    printf(".-.");
  } else if (c == 76) {
    printf(".-..");
  } else if (c == 77) {
    printf("--");
  } else if (c == 78) {
    printf("-.");
  } else if (c == 79) {
    printf("---");
  } else if (c == 80) {
    printf(".--.");
  } else if (c == 81) {
    printf("--.-");
  } else if (c == 82) {
    printf(".-.");
  } else if (c == 83) {
    printf("...");
  } else if (c == 84) {
    printf("-");
  } else if (c == 85) {
    printf("..-");
  } else if (c == 86) {
    printf("...-");
  } else if (c == 87) {
    printf(".--");
  } else if (c == 88) {
    printf("-..-");
  } else if (c == 89) {
    printf("-.--");
  } else if (c == 90) {
    printf("--..");
  }
}
