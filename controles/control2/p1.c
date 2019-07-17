struct Param{
	int a[];
	int n;
	int ini;
	int end;
	Set res;
};

Set buscar(int a[], int n){
	Set comb = (1<<(n-1)<<1) - 1;
	Set delta = 1<<(n-3);
	Param parms[8];
	pthread_t t[8];
	for (int j = 0; j < 8; j++){
		parms[j].n = n;
		parms[j].a = a;
		parms[j].ini = delta*j + 1;
		parms[j].end = j == 7 ? comb : delta*(j+1);
		pthread_create(&t[j], NULL, thread_fun, &parms[j]);
	}
	Set ret = 0;
	for(int j = 0; j < 8; j++){
		pthread_join(t[j], NULL);
		if (parms[j].res != 0) ret = parms[j].ret;
	}
	return ret;
} 

void *thread_fun(void *ptr){
	Param *parm = ptr;
	int *a = parm->a, n = parm->n;
	Set ini = parm->ini, end = parm-> end;
	for (Set k = ini; k<=end; k++){
		long long sum = 0;
		for(int i = 0; i<n; i++){
			if (k&((Set)1<<i)) sum += a[i];
		}
		if (!sum){
			parm->res = k;
			return NULL;
		}
	}
	parm -> res = 0;
	return NULL;
}