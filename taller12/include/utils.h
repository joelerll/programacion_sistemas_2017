int numero_lineas(char *ruta, int *tam_lineas);
char** recolectarPalabras(int nPalabras, char **argv);
char** dividirArchivo(char *ruta, int partes, int tamano);
int getTotalCaracteresArchivo(int numLineas, int *numCaracteresXLinea);
void contarOcurrencias(char **palabrasABuscar, char *texto, int *numOcurrencias, int numPalabrasABuscar);