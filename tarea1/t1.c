
// Tarea 1 PSS, F. Giovanni Sanguineti

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

uint concat_bits(uint x, int n, uint y, int m){
	return ((x & ~(-1<<n)) << m) | (y & ~(-1<<m));
}

char* eliminados(char *str, char *pat){

    char *str_pointer = str;
    char *pat_pointer = pat;

    int str_len = strlen(str);
    int pat_len = strlen(pat);

    int new_len = str_len;

    // calcular el tamaño del nuevo arreglo
    while(*str_pointer){
        if (*str_pointer==*pat_pointer){
            int i = 1;
            str_pointer++;
            pat_pointer++;
            while(*pat_pointer){
                if (*str_pointer==*pat_pointer) {
                    str_pointer++;
                    pat_pointer++;
                    i++;
                    }
                else {
                    break;
                    }
                }
            if (i==pat_len) {
                new_len -= pat_len;
                pat_pointer = pat;
                }
            else{
                str_pointer -= (i-1);
                pat_pointer = pat;
            }
        }
        else{
            str_pointer++;
        }
    }
    str_pointer = str;
    char *newstring = malloc((sizeof(char)*(new_len + 1)));
    char *tonewstring = newstring;

    while(*str_pointer){

        if (*str_pointer==*pat_pointer){
            int i = 1;
            str_pointer++;
            pat_pointer++;
            while(*pat_pointer){
                if (*str_pointer==*pat_pointer) {
                    str_pointer++;
                    pat_pointer++;
                    i++;
                }
                else {
                    break;
                }
            }
            if (i==pat_len) {
                pat_pointer = pat;
            }
            else{
                str_pointer -= i;
                *tonewstring = *str_pointer;
                str_pointer++;
                tonewstring++;
                pat_pointer = pat;
            }
        }
        else{
            *tonewstring = *str_pointer;
            tonewstring++;
            str_pointer++;
        }
    }
    *tonewstring = 0;

    return newstring;

}

void eliminar(char *str, char *pat){
    char *str_pointer = str;
    char *save = str;
    char *pat_pointer = pat;
    int pat_len = strlen(pat);

    int success_len = 0;

    while(*str_pointer){
        if (*str_pointer==*pat_pointer){
            int i = 1;
            str_pointer++;
            pat_pointer++;
            while(*pat_pointer){
                if (*str_pointer==*pat_pointer) {
                    str_pointer++;
                    pat_pointer++;
                    i++;
                }
                else {
                    break;
                }
            }
            if (i==pat_len) {
                pat_pointer = pat;
                char* aux_pointer = str;
                for(int j = success_len; j > 0; j--){
                    char* inicio = aux_pointer + j - 1;
                    char* destino = aux_pointer + j+ pat_len - 1;
                    *destino = *inicio;
                }
                str += pat_len;
            }
            else{
                str_pointer -= (i-1);
                success_len++;
                pat_pointer = pat;
            }
        }
        else{
            str_pointer++;
            success_len++;
        }
    }
    strcpy(save,str);
}
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

