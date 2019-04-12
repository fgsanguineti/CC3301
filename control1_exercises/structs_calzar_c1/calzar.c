#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int x;
    struct nodo *izq, *der;
} Nodo;

int calzar(Nodo *a, Nodo **ppat){

    Nodo *checker = *ppat;
    Nodo *toTree = a;

    if (!checker){ // caso base en que puntero apunta a vacio
        *ppat = a;
        return 1;
    }
    if (!toTree) return 0;

    if (checker->x == toTree->x){ //recursión
        int izq =calzar(toTree->der, &checker->der);
        int der =calzar(toTree->izq, &checker->izq);
        return (izq && der);


    }
    return 0;


}

