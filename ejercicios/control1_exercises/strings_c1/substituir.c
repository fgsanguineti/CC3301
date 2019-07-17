#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int espacio(char *s, char *p, char *r) {
  char *toword = s;
  char *tolooked = p;
  int wordsize =strlen(s);
  int lookedsize =strlen(p);
  int substsize = strlen(r);
  int finalsize = wordsize + 1;

  while(*toword){
    int cmp = strncmp(toword,tolooked,lookedsize);
    if(!cmp){
        finalsize += (substsize - lookedsize);
        toword += lookedsize;
        continue;
    }
    toword++;
  }
  return finalsize;
}

char *substituir(char *s, char *p, char *r) {
    char* newstring = (char*)(malloc(espacio(s,p,r)*sizeof(char*)));

    char *toword = s;
    char *tolooked = p;
    char *tosubst = r;
    int lookedsize =strlen(p);
    int substsize = strlen(r);

    while(*toword){
        int cmp = strncmp(toword,tolooked,lookedsize);
        if(!cmp){
            strcpy(newstring,tosubst);
            toword += lookedsize;
            newstring += substsize;
        }
        *newstring = *toword;
        toword++;
        newstring++;
    }

    *newstring = 0;
    newstring -= espacio(s,p,r) -1;
    return newstring;
}

int main() {
    char * a = substituir("hola mundo", "ola", "ello");
  if (espacio("hola mundo", "hello", "bonjour")!=11)
    printf("falla test 1\n");
  else if (espacio("hola mundo", "ola", "ello")!=12)
    printf("falla test 2\n");
  else if (espacio("elgatotemelperro", "el", "un")!=17)
    printf("falla test 3\n");
  else if (strcmp(substituir("hola mundo", "hello", "bonjour"),
             "hola mundo") != 0)
    printf("falla test 4\n");

  else if (strcmp(substituir("hola mundo", "ola", "ello"),
                  "hello mundo") != 0)
    printf("falla test 5\n");
  else if (strcmp(substituir("elgatotemelperro", "el", "un"),
                  "ungatotemunperro") != 0)
    printf("falla test 6\n");
  else
    printf("Todos los tests funcionan correctamente\n");
  return 0;
}

