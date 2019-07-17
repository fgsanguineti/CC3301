#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "jsocket.h"
#include "util.h"

typedef void *(*Thread_fun)(void *);
typedef unsigned long long ulonglong;
typedef unsigned int uint;

#define DELTA 1.0/1000.0;
#define EPSILON 0.0000000001
double total = 0;
double base = 0;
int clientes = 0;

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;

void *serv(long s){
	clientes++;
  	while(1) {
  	pthread_mutex_lock(&m);
    double i= base;
    double j = base + DELTA;
    double resultado;
    if (j > 1 + EPSILON){
    	clientes--;
    	pthread_mutex_unlock(&m);
    	break;
    }
    base = j;
    pthread_mutex_unlock(&m);

    printf("env [%.3f, %.3f]\n", i, j);
    write(s, (char*)&i, sizeof(i));
    write(s, (char*)&j, sizeof(j));
    leer(s, (char*)&resultado, sizeof(double));

  	pthread_mutex_lock(&m);
  	total += resultado;
  	pthread_mutex_unlock(&m);
	}
	if (clientes==0) printf("integral= %f \n", total);
	close(s);
  return NULL;
}
 
int main(int argc, char **argv) {
  long s, s2;
  pthread_t pid;
  signal(SIGPIPE, SIG_IGN);
  s = j_socket();
  if (j_bind(s, 3000) < 0) error("bind falló.  Port 3000 ocupado?");

  while(1) {
    pthread_attr_t attr;
    s2= j_accept(s);
    pthread_attr_init(&attr);
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
      fprintf(stderr, "No se puede establecer el atributo\n");
    }
    if (pthread_create(&pid, &attr, (Thread_fun)serv, (void *)s2) != 0) {
      fprintf(stderr, "No pude crear thread para nuevo cliente %ld!!!\n", s2);
      close(s2);
    }
    pthread_attr_destroy(&attr);
  }
}


