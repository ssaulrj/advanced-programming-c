#include <stdio.h>
#include <wait.h>
#include <unistd.h>

int main()
{
	int pid, i;
	printf("Abuelo es: %i \n",getppid() ); 
	for(i=0; i<=3; i++)
	{
		pid=fork();
		if(pid==-1)
		{ printf("Ocurrio un error \n");}
		else if (pid==0)
		{printf("Código del proceso hijo %i \n", getpid()  );
		printf("Código del proceso padre %i \n", getppid() );}
		else if ( pid>0)
		{wait (&pid);}
        }
return(0);
}
