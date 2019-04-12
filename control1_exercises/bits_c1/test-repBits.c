/* Modifique la funcion repBits para que cumpla con el enunciado del control 1
 * del semestre Otono 2013.  El enunciado esta en:
 * http://users.dcc.uchile.cl/~lmateu/CC3301/controles/c1-131.pdf
 */

#include <stdio.h>
#include <stdlib.h>

/* entrega una mascara con los k bits menos significativos en 1 */
unsigned mascara(unsigned k) {
  return k==32 ? -1 : (1<<k)-1;
}

/* Modifique esta funcion para que pasen todos los tests */

unsigned repBits(unsigned x, int i, int k, unsigned val){
    unsigned wea = ~((-1)<< k);
    unsigned mask = (val & wea) << i;
    int wea2 = ~(wea<< i);
    unsigned pre_resultado = wea2 & x;
    return pre_resultado | mask;
}

int main() {
  /* Test 1 */
    unsigned t0= repBits(51, 3, 2, 5);
    if (t0!=43) {
        fprintf(stderr, "fallo el test 0\n");
        exit(1);
    }

  unsigned t1= repBits(0x12345678, 0, 4, 0xf);
  if (t1!=0xf2345678) {
    fprintf(stderr, "fallo el test 1\n");
    exit(1);
  }

  /* Test 2 */
  unsigned t2= repBits(0x12345678, 4, 8, 0xaa);
  if (t2!=0x1aa45678) {
    fprintf(stderr, "fallo el test 2\n");
    exit(1);
  }

  /* Test 3 */
  unsigned t3= repBits(0x00000000, 31, 1, 1);
  if (t3!=0x00000001) {
    fprintf(stderr, "fallo el test 3\n");
    exit(1);
  }

  /* Test 4 */
  unsigned t4= repBits(0x89abcdef, 0, 32, 0x12345678);
  if (t4!=0x12345678) {
    fprintf(stderr, "fallo el test 4\n");
    exit(1);
  }

  printf("Todos los tests pasaron exitosamente\n");

  return 0;
}
