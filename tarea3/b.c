#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int compartiendo = false;
int readers = 0;

void *recurso = NULL;

void devolver() {
    pthread_mutex_lock(&m);
    readers--;
    if (readers == 0) pthread_cond_broadcast(&c);
    pthread_mutex_unlock(&m);
}

void *acceder() {
    pthread_mutex_lock(&m);
    readers++;
    pthread_cond_broadcast(&c);
    while (!compartiendo) pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);
    return recurso;
}

void compartir(void *ptr) {
    pthread_mutex_lock(&m);
    while (readers == 0) pthread_cond_wait(&c, &m);
    compartiendo = true;
    recurso = ptr;
    pthread_cond_broadcast(&c);

    while (readers > 0) pthread_cond_wait(&c, &m);
    pthread_cond_broadcast(&c);
    compartiendo = false;
    recurso = NULL;
    pthread_mutex_unlock(&m);
}