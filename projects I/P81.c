#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main ()
{
	
	int incremento;
	int pid, i,var,ret;

        ret=fork();
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
return(0);
}
