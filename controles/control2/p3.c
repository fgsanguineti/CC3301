int damas = 0;
int varones = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void entrarVaron(){
	pthread_mutex_lock(&m);
	while (damas > 0) pthread_cond_wait(&c, &m);
	varones++;
	pthread_mutex_unlock(&m);
}
void salirVaron(){
	pthread_mutex_lock(&m);
	varon--;
	pthread_cond_broadcast(&c);
	pthread_mutex_unlock(&m);
}
void entrarDama(){
	pthread_mutex_lock(&m);
	while(varones > 0) pthread_cond_wait(&c, &m);
	damas++;
	pthread_mutex_unlock(&m);
}
void salirDama(){
	pthread_mutex_lock(&m);
	damas--;
	pthread_cond_broadcast(&c);
	pthread_mutex_unlock(&m);
}