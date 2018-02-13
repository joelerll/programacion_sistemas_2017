typedef struct InfoArreglo {
    long *inicio;
    long *fin;
    long tamano;
}infoArreglo;

infoArreglo ** funcionDivInfo(long *arraylong, long lenArray, long nHilos);