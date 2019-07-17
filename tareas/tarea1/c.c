#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

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
