#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

// #define N 5
int N = 0;
// int buffer[N];
float TIEMPO_CONSUMER = 0.0;
float TIEMPO_PRODUCER = 0.0;
int entrada = 1;
int salida = 1;
int contador = 1;
int items_consumidos = 0;
int cola = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lleno = PTHREAD_COND_INITIALIZER;
pthread_cond_t vacio = PTHREAD_COND_INITIALIZER;

void *func_proc(void *arg) {
  pthread_mutex_lock(&mutex);
  if (entrada) {
    printf("Productor %d ha producido 1 item, tamano cola %d\n",(int*)arg, N);
  }
  while ( contador == N ) {
    entrada = 0;
    pthread_cond_wait(&lleno, &mutex);
    entrada = 1;
  }
  contador= contador + 1;
  usleep(TIEMPO_PRODUCER);
  pthread_cond_broadcast(&vacio);
  pthread_mutex_unlock(&mutex);
}

void *func_cons(void *arg) {
  pthread_mutex_lock(&mutex);
  if (salida) {
    printf("Consumidor %d ha consumido 1 item, tamano cola %d\n",(int*)arg, N);
  }
  while (contador==0) {
    salida = 0;
    pthread_cond_wait(&vacio, &mutex);
    salida = 1;
  }
  contador= contador - 1;
  sleep(TIEMPO_CONSUMER);
  pthread_cond_broadcast(&lleno);
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[]) {

  int num_hilos_prod = atoi(argv[1]);
  int tiempo_prod = atof(argv[2]);
  int num_hilos_cons = atoi(argv[3]);
  int tiempo_cons = atof(argv[4]);
  int tam_cola = atoi(argv[5]);
  int total_items = atoi(argv[6]);
  int estado_productores, estados_consumidores;
  N = tam_cola;
  TIEMPO_PRODUCER = tiempo_prod * 1000000;
  TIEMPO_CONSUMER = tiempo_cons * 1000000;

  pthread_t *hilos_productores = malloc(sizeof(pthread_t) * num_hilos_prod);

  for (size_t i = 0; i < num_hilos_prod; i++) {
    estado_productores = pthread_create(&hilos_productores[i], NULL, func_proc, (void *)i);
    if (estado_productores < 0) {
      exit(-1);
    }
  }

  pthread_t *hilos_consumidores = malloc(sizeof(pthread_t) * num_hilos_cons);
  //
  for (size_t i = 0; i < num_hilos_cons; i++) {
    estado_productores = pthread_create(&hilos_consumidores[i], NULL, func_cons,  (void *)i);
    if (estado_productores < 0) {
      exit(-1);
    }
  }

  for (size_t i = 0; i < num_hilos_prod; i++) {
    estado_productores = pthread_join(hilos_productores[i], NULL);
    if (estado_productores < 0) {
      exit(-1);
    }
  }

  for (size_t i = 0; i < num_hilos_cons; i++) {
    estado_productores = pthread_join(hilos_consumidores[i], NULL);
    if (estado_productores < 0) {
      exit(-1);
    }
  }

  // pthread_create(&hcons, NULL, func_cons, NULL);
  // pthread_join(hprod, NULL);
  // pthread_join(hcons, NULL);

  return 0;
}
