#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
  int v;
  struct nodo *izq, *der;
} Nodo;

Nodo **rama(Nodo *a, int v, int *p) {
    Nodo *nodito = a;
    *p = 0;
    while(1){
        if (nodito==NULL) {
            *p = 0;
            return nodito;
        }
        else if (nodito->v==v){
            *p = *p + 1;
            break;
        }
        else if (nodito->v > v){
            *p = *p + 1;
            nodito = nodito->izq;
            continue;
        }
        else if (nodito->v < v){
            *p = *p + 1;
            nodito = nodito->der;
            continue;

        }
    }
    nodito = a;
    Nodo** arreglo;
    arreglo = (Nodo**)malloc(*p * sizeof(Nodo*));
    for(int i = 0; i< *p-1; i++){
        arreglo[i] = malloc((sizeof(Nodo*)));
    }

    int x = 0;
    while (x<p){
        if (nodito->v > v){
            arreglo[x] = nodito;
            nodito = nodito->izq;
            x++;
        }
        else{
            arreglo[x] = nodito;
            if (nodito->v==v){
                break;
            }
            nodito = nodito->der;
            x++;
        }

    }
    return arreglo;
}

Nodo nodos[]= {
  { 0, NULL, NULL}, /* no se usa */
  { 10, NULL, NULL},
  { 20, &nodos[1], NULL},
  { 30, &nodos[1], &nodos[6]},
  { 40, NULL, NULL},
  { 50, &nodos[4], NULL},
  { 60, &nodos[5], &nodos[7]},
  { 70, NULL, NULL} };

int main() {
  Nodo *a= &nodos[3];
  int n;
  Nodo **r= rama(a, 50, &n);
  if (n!=3)
    printf("n debio ser 3, no %d\n", n);
  if (r[0]->v!=30)
    printf("el primer nodo debio ser 30, no %d\n", r[0]->v);
  else if (r[1]->v!=60)
    printf("el segundo nodo debio ser 60, no %d\n", r[1]->v);
  else if (r[2]->v!=50)
    printf("el tercer nodo debio ser 50, no %d\n", r[2]->v);

  if (rama(a, 55, &n)!=NULL)
    printf("55 no debe estar en el arbol\n");
  return 0;
}
