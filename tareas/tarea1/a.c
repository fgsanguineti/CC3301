#include "t1.h"

uint concat_bits(uint x, int n, uint y, int m){
	return ((x & ~(-1<<n)) << m) | (y & ~(-1<<m));
} 
