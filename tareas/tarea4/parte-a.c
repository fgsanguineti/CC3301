#include "integral.h"

double integral(Funcion f, void *p, double xi, double xf, int n) {
	double h = (xf - xi)/n;
	double a = ((f(p,xi) + f(p,xf))/2);
	double b = 0;
	for(int i = 1; i< n; i++){
		b += f(p, xi+i*h);
	}
	return h*(a+b);
}
