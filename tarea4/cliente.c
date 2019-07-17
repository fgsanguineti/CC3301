#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "jsocket.h"
#include "util.h"
#include "integral.h"

int main(int argc, char **argv) {
  long s;
  s = j_socket();
  if (j_connect(s, "localhost", 3000)<0)
    error("conexión rechazada");

  while(1){
    double i, j, res;
    if (leer(s, (char*)&i, sizeof(i))){
      	break; 
    }
    if (leer(s, (char*)&j, sizeof(j))) error("falló la conexion");
  	printf("rec [%.3f, %.3f]\n", i,j);
    res= integral_f(i, j);
    write(s, &res, sizeof(res));
  }
  close(s);
  return 0;
}
