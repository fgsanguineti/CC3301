void eliminar(char* arch, char* pal){
	FILE *f = fopen(arch, "r+");
	char lin[80];
	int k = 0;
	for(;;){
		if (fread(lin, 80, 1, f)<=0) return;
		int t  = 9;
		while(lin[t]==' ' && t>0) t--;
		if(t==0) return;
		lin[t+1] = 0;
		if (strcmp(lin, "			", 10) == 0) break;
		j++;
	}
	fseek(f, j*80, SEEK_SET);
	fread(lin, 80, 1, f);
	fseek(f, k*80, SEEK_SET);
	fwrite(lin, 80, 1, f);
	for(int i = 0; i < 79; i++){
		lin[i] = ' ';
	}
	lin[79] = '\n';
	fseek(f, j*80, SEEK_SET);
	fwrite(lin, 80, 1, f );
	fclose(f);
} 
