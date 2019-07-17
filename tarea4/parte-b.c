#include "integral.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "util.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
	pid_t pid[p];
	int fds[p];
	double res[p];
	double h = (xf-xi)/p;
	for(int i = 0; i < p; i++){
		int fd[2];
		pipe(fd);
		fds[i] = fd[0];
		if((pid[i]=fork())==0){
			res[i] = integral(f, ptr, xi+i*h, xi + (i+1)*h,n);
			write(fd[1], &res[i], sizeof(double));
			close(fd[1]);
			close(fd[0]);
			exit(0);
		}
		else{
			close(fd[1]);
		}
	}
	for (int j = 0; j < p; j++){
		read(fds[j], &res[j],sizeof(double));
		close(fds[j]);
	}
	for (int k = 0; k < p; k++){
		waitpid(pid[k], NULL, 0);
	}

	double r = 0.0;

	for (int a = 0; a < p; a++){
		r += res[a];
	}
	return r;
}

