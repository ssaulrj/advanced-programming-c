#include <stdio.h>
#include <unistd.h>

int pid=0;
int main()
{
	pid=fork();
	if(pid==-1)
	{ printf("Ocurrio un error \n");}
	else if (pid==0)
	{printf("Código del proceso hijo %i \n", getpid()  );}
	else
	{printf("Código del proceso padre %i \n", getpid() );}

return(0);
}
