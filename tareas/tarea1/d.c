#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

int k_primeros(Nodo **pa, int k){
    Nodo *a = *pa;
    if (k==0){
        *pa = NULL;
        return 0;
    }
    else if (a==NULL)
        return 0;
    else {
        int kizq = k_primeros(&a->izq, k);
        int kder = k_primeros(&a->der, k);
        int hijos = kizq + kder;
        if (kizq == k) {
            *pa = a->izq;
            return k;
            }
        else if (k == hijos){
            Nodo* aux = a->der;
            Nodo* prevaux = a;
            while(aux->der!=NULL){
                prevaux = aux->der;
                aux = aux->der;
            }
            if (aux->izq!=NULL){
                *prevaux->der = *aux->izq;
                return k;
            }
            prevaux->der = NULL;
            return k;
        }
        return hijos + 1;
    }
}

