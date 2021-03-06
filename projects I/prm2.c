#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main ( int argc, char *argv[] ){
	if( argc!=2 ){
		printf("Numero de parametros incorrectos, Uso: %s [entero]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int ret;
	int var=atoi(argv[1]);
	char c;
	int i;
	
	printf("el tamaño de %s es: %i\n",strlen(argv[1]));
	
	for(i=0; i<strlen(argv[1]); i++){
		c=argv[1][i];
		if(isdigit(c)==0){
			exit(EXIT_FAILURE);
		}
	}
	ret=fork();
	if(ret==-1){
		perror("Fallo en fork()\n");	
		exit(EXIT_FAILURE);
	} else if(ret>0){
		var+=2;
		printf("Padre: %i\n",var);
		wait(NULL);
	} else if(ret==0){
		var-=4;
		printf("Hijo: %d\n",var);
		exit(EXIT_SUCCESS);
	}
}
