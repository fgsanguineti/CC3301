#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "t1.h"

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