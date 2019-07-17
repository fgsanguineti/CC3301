#include "t2.h"

int buscar(void *a, int n, void *x, Comparador cmp){
    int izq = 0; int der = n - 1; int mid = 0; int index = -1;
    int comp;
    while (izq <= der){

        mid = izq + (der - izq)/2;

        comp = (*cmp)(a, mid, x);
        if (comp == 0) {
            index = mid;
            break;
        }
        else if (comp < 0){
            izq = mid + 1;
        }
        else{
            der = mid - 1;
        }
    }
    return index;
}
