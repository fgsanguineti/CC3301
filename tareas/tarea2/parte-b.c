#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t2.h"

int linecmp(void *a, int k, void *x) {
    FILE *file = fopen(a, "r");
    char *palabra = malloc(sizeof(char)*80);
    char *puntos = ":\0";
    strcat(palabra,x);
    strcat(palabra,puntos);
    int strsize = strlen(palabra);
    char buf[strsize+1];
    fseek(file,ANCHO*k,SEEK_SET); //
    fread(buf,1,strlen(palabra),file);
    fclose(file);
    buf[strsize] = 0;
    int comparision = strncmp(buf, palabra,strsize);
    free(palabra);
    return comparision;
}

void linecleaner(char *a) {
    char* aux = a;
    int number = 0;
    while(*aux){
        if (*aux==':'){
            if (number==0){
                strcpy(a,aux+1);
                number++;
            }
            else {*aux = 0; break;}
        }
        aux++;
    }
}

char *consultar(char *nom_dic, char *pal, int n_lin){
    char *lineacompleta;
    char *malloquear = malloc(sizeof(char)*ANCHO);
    FILE *file = fopen(nom_dic,"r");
    int linea = buscar(nom_dic,n_lin,pal,linecmp);
    if (linea==-1) {free(malloquear); return NULL; }
    else{
        char buf[ANCHO];
        fseek(file, ANCHO*linea, SEEK_SET);
        fread(buf,1,ANCHO,file);
        lineacompleta = buf;
        fclose(file);
        linecleaner(lineacompleta);
        strcpy(malloquear,lineacompleta);
        return malloquear;
    }
}


