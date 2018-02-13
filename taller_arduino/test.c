#include <stdio.h>    // Standard input/output definitions
#include <stdlib.h>
#include <string.h>   // String function definitions
#include <unistd.h>   // para usleep()
#include <getopt.h>
#include <math.h>

#include "arduino-serial-lib.h"

float calculateSD(float data[]);

void error(char* msg)
{
    fprintf(stderr, "%s\n",msg);
    exit(EXIT_FAILURE);
}
int ugetchar(void);

int main(int argc, char *argv[])
{
	int fd = -1;
	int baudrate = 9600;  // default

	fd = serialport_init("/dev/ttyACM0", baudrate);
  char uno = '1';
  char cero = '0';
  char modelo = 'i';
  char temperatura = 't';
  int humedad_arreglo[100];
  int temperatura_arreglo[100];
  char humedad = 'h';
  char buf[10];
  int temp;
  int humeda;
  size_t nbytes;
  size_t nbytes2;
  nbytes = sizeof(temp);
  nbytes2 = sizeof(humeda);
  int cont = 0;

  while (1) {
    /*temperatura*/
    write(fd, &temperatura, 1);
    usleep(1000000);
    read(fd, &temp, nbytes);
    usleep(1000000);

    /* humedad */
    write(fd, &humedad, 1);
    usleep(3000000);
    read(fd, &humeda, nbytes);
    printf("La temperatura es: %d\n", temp);
    printf("La humedad es: %d\n", humeda);
    cont++;
    humedad_arreglo[cont] = humeda;
    temperatura_arreglo[cont] = temp;

  }

  buf[13] = '\0';
  // read(fd, &model, 1);
  // read(fd, model, 1);
  // write(fd, &uno, 1);
  printf("%s\n", buf);
  // char ch;
  // int cont = 0;
  // while(read(STDIN_FILENO, &ch, 1) > 0)
  // {
  //    cont++;
  //    printf("%s\n", );
  // }
  // write(fd, &uno, 1);
  // usleep(1000000);
  // write(fd, &cero, 1);
  // usleep(1000000);
  // write(fd, &uno, 1);
  // usleep(1000000);
  // write(fd, &cero, 1);
  // usleep(1000000);
  // write(fd, &uno, 1);
  // usleep(1000000);
  // write(fd, &cero, 1);
  // usleep(1000000);
  // write(fd, &uno, 1);
  // usleep(1000000);
  // write(fd, &cero, 1);
	if( fd==-1 )
	{
		error("couldn't open port");
		return -1;
	}


	close( fd );
	return 0;
}

/* Ejemplo para calcular desviacion estandar y media */
float calculateSD(float data[])
{
    float sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for(i = 0; i < 10; ++i)
    {
        sum += data[i];
    }

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
}
