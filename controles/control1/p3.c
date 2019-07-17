void cortar(Nodo** plista, char *pal, Nodo** pres){
	Nodo* ultimo = *plista;
	Nodo* siguiente = ultimo -> prox;
	while(*ultimo){
		if(!siguiente -> prox) return;
		if(!(siguiente-> pal)){
			*pres = siguiente;
			ultimo -> prox == NULL;
			return;
		}
		ultimo = siguiente;
		siguiente = siguiente -> prox;
	}
	return;
} 
