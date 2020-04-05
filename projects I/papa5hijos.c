#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>


int main()
{ 	int incremento;
	int pid, i;


	for(i=0; i<=4; i++)
	{
		pid=fork();
		if(pid)
		{
			printf("Padre: %i\n",getpid() );
			wait (&pid);
		} 

		else 
		{printf("Código del proceso (PID) hijo %i, valor de la variable: %i, mi padre es: %i \n", getpid(),i,getppid()  );}
        }



return(0);
}


