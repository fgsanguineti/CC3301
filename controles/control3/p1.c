int viajante_par(int z[], int n, int **m, int nperm, int p){
	pid_t pid[p];
	int fds[p], resultados[p];
	int global_min = INT_MAX;
	double** rutas = calloc(p, (n+1)*sizeof(int));
	for(int i= 0; i<p; i++){
		int fd[2];
		pipe(fd);
		fds[i] = fd[0];

		if((pid[i] = fork())==0){
			int local_min = INT_MAX;
			int local_ruta[n+1];
			for(int j = 1; j < nperm; j++){
				int x[n+1];
				x[0] = 0;
				genperm(&x[1], n);
				int d = dist(x, n, m);
				if(d < local_min){
					local_min = d;
					for(int k = 0; k <= n; k++){
						local_ruta[k] = x[k];
					}
				}
			}
			write(fd[1], &local_min, sizeof(int));
			write(fd[1], local_ruta, sizeof(local_ruta))
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
		else{
			close(fd[0]);
		}
	}

	for(int a = 0; a < p; a++){
		leer(fds[a], &resultados[p], sizeof(int));
		leer(fds[a], rutas[p], sizeof(rutas[p]));
		close(fds[k]);
	}
	for(int b = 0; b < p; b++){
		waitpid(pid[b], NULL, 0);
	}
	for (int c = 0; c < p; c++){
		if(resultados[c] < global_min){
			global_min = resultados[c];
			double *fila = rutas[c];
			for(int d = 0; d<n; d++){
				z[d] = fila[d]
			}
		}
	}
	return global_min;
}