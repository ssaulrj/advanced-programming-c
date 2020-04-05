#include <stdio.h>
#include <wait.h>
#include <unistd.h>

int incremento=1;
int procesoshijos[6];
int a=1,a2=2,a3=3,a4=4,a5=5;

int main()
{
	int pid, i,x;
	for(i=1; i<=5; i++)
	{       
		pid=fork();
		if(pid==-1)
		{ 
		printf("Ocurrio un error \n");
		}
		else if (pid==0)
		{
		procesoshijos[i]=getpid();
				printf("Hijo: %i - Variable: %i - Global: %i - Padre: %i \n", 					getpid(), i+incremento, incremento, getppid()  ); 
				printf("areglo %d \n", procesoshijos[i]);
				printf("i %i\n",i);
		break;
		/* break hacer padre con x hijos*/	
		}
		//else if (pid>0)
		//{wait (&pid); 
		/* break;  break para hacer padre e hijo padre e hijo*/ 
		//}
            incremento++;	
        }

/*while(1)
{
	if(procesoshijos[i]!=0)
	{
		if(procesoshijos[i]==getpid())
		{
			if(i==1){printf("Código del proceso hijo %d, valor: %i \n", procesoshijos[1], a=a+1);}
			if(i==2){printf("Código del proceso hijo %d, valor: %i \n", procesoshijos[2], a2=a2+2);}
			if(i==3){printf("Código del proceso hijo %d, valor: %i \n", procesoshijos[3], a3=a3+3);}
			if(i==4){printf("Código del proceso hijo %d, valor: %i \n", procesoshijos[4], a4=a4+4);}
			if(i==5){printf("Código del proceso hijo %d, valor: %i \n", procesoshijos[5], a5=a5+5);}
		}	
	}
}
wait (&pid);*/  
return(0);
}
