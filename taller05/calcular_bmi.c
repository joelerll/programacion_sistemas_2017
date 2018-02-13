#include "datos.h"

float calcularBMI(float pesoKg, float alturaMetros) {
  float cuadrado = alturaMetros * alturaMetros;
  return pesoKg/cuadrado;
}
