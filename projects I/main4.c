#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid, i;
	for(i=1; i<=3; i++)
	{
		pid=fork();
		if(pid==-1)
		{ printf("Ocurrio un error \n");}
		else if (pid==0)
		{printf("C�digo del proceso hijo %i \n", getpid()  );}
		else
		{printf("C�digo del proceso padre %i \n", getpid() );}
        }
return(0);
}
