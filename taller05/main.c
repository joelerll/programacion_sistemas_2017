#include <stdio.h>
#include "datos.h"

int main(int argc, char const *argv[]) {
  char *nombres = "joel eduardo \n";
  mostarNombre(nombres);
  float bmi = calcularBMI(5.0,2.0);
  printf(" Calcular BMI: %9.6f  \n", bmi);
  float agua_c = calcularAguaCorporal(5.0,3.0);
  printf("Calcular Agua Corporal: %9.6f  \n", agua_c);
  float tasa = calcularTasaMetabolica(8.3);
  printf("Calcular Tasa Metabolica: %9.6f \n", tasa);
  float ritmo = calcularRitmoCarRes(8.0);
  printf("Calcular Ritmo Car: %9.6f \n", ritmo);
  return 0;
}
