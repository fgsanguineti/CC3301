#include <pthread.h>
#include <stdlib.h>

typedef int (*BoolFun)(int x[]);

typedef struct {
    BoolFun f;
    int *array_pointer;
    int res;
    int n;
} Args;

void gen(int *x, int i, int n, BoolFun f, int* res) {
    if (i == n) {
        if ((*f)(x)) {
            *res = *res + 1;
        }
    } else {
        x[i] = 0;
        gen(x, i + 1, n, f, res);
        x[i] = 1;
        gen(x, i + 1, n, f, res);
    }
}

void *multi_thread(void *ptr) {
    Args *a = ptr;
    gen(a->array_pointer, 3, a->n, a->f, &(a->res));
    free(a->array_pointer);
    return NULL;
}

void combinar(int *x, int i, int n, int** array, int* in) {
    if (i == n) {
        *array[*in] = x[0];
        *(array[*in] + 1) = x[1];
        *(array[*in] + 2) = x[2];
        *in = *in + 1;
    } else {
        x[i] = 0;
        combinar(x, i + 1, n, array, in);
        x[i] = 1;
        combinar(x, i + 1, n, array, in);
    }
}

int recuento(int n, BoolFun f) {
    int in = 0; int*p = &in;
    int **array = calloc(8, 3 * sizeof(int));
    for (int x = 0; x < 8; x++) {
        array[x] = calloc(3, sizeof(int));
    }
    int first[3] = {0,0,0};
    combinar(first, 0, 3, array, p);
    pthread_t t[8];
    Args argumentos[8];

    for (int x = 0; x < 8; x++) {
        Args *arg = &argumentos[x];
        arg->array_pointer = array[x];
        arg->array_pointer = realloc(arg->array_pointer, n * sizeof(int));

    }
    free(array);

    for (int x = 0; x < 8; x++) {
        Args *arg = &argumentos[x];
        arg->n = n;
        arg->f = f;
        arg->res = 0;
        pthread_create(&t[x], NULL, multi_thread, arg);
    }
    for (int x = 0; x < 8; x++) {
        pthread_join(t[x], NULL);
    }
    int resultado = 0;

    for (int x = 0; x < 8; x++) {
        Args *arg = &argumentos[x];
        resultado += arg->res;
    }
    return resultado;
}