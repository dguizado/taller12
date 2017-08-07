#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

int argv[];
#define Num_threads argv[3]

pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;


int numero_lineas(char *ruta, int *tam_lineas){
	if(ruta != NULL){
		FILE* ar = fopen(ruta, "r");
		int lineas = 0;
		int tam_linea;
		while(!feof(ar)){
			tam_linea++;
			char c = getc(ar);
			if(c == '\n'){
				if(tam_lineas != NULL){
					tam_lineas[lineas] = tam_linea;
				}
				lineas++;
				tam_linea = 0;
			}
		}
		fclose(ar);
		return lineas;
	}
	return -1;
}


int LineasPorHilo(char* ruta){
	int c;
	int totalLineas;
	int *tam_lineas;
	c=numero_lineas(ruta,tam_lineas);
	totalLineas=(c/Num_threads);
	return totalLineas;
}


void funcionHilo(char* palabras[]){

	int j;
	int a;
	int i;
	int cont=0;
	int num_palabras[sizeof*(palabras)];
	char *pal;


	FILE* fp = fopen("/root/taller12/final.txt","r");
	a=LineasPorHilo("/root/taller12/final.txt");

	if(fp == NULL)
		printf("Error al abrir el archivo");

	while(!feof(fp)){
		for(i=0; i<Num_threads; i++){
			for(j=0; j<sizeof*(palabras);j++){
				pthread_mutex_lock(&mutex);
				int p= fseek(fp,(a+1),SEEK_SET);
				char* linea=fgets(linea,p,fp);
				pal=strtok(linea," ");
				if(pal==palabras[j]){
				cont++;
				num_palabras[cont];
				pthread_mutex_unlock(&mutex);
				}
			}
		}


	}


}


int main(int argc, char argv[]){
	int i;


	for(i=4;i<argc;i++){
	char palabras[argv[i]];
	}


	pthread_t threads[Num_threads];
	int rc;
	int t;
	for(t=0; t<Num_threads; t++){
		rc=pthread_create(&threads[t],NULL,(void*)funcionHilo,(void*)t);
		if(rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		} 
	}
	pthread_exit(NULL);
}
