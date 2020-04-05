#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main ( int argc, char *argv[] ){
	if( argc!=2 ){
		printf("Numero de parametros incorrectos, Uso: %s [entero]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int var=atoi(argv[1]);
	printf("Entrada: %i\n", var);
	
	int ret=fork();
	if(ret>0){
		var+=2;
		printf("Padre: %i\n",var);
		wait(NULL);
	} else if(ret==0){
		var-=4;
		printf("Hijo: %d\n",var);
		exit(EXIT_SUCCESS);
	} else if(ret==-1){
		perror("Fallo en fork()\n");	
		exit(EXIT_FAILURE);
	}
}

