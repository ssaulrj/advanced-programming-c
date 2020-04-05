#include<stdio.h>
#include<unistd.h>
#include<wait.h>
#include<time.h>
#include <string.h>
#define MAXLINEA 100
void VerDatos();
void PonerDatos();
int Comprobar();

int main()
{

int pid,i;
int a[5];
int c=0;
int padre,hijo;
padre = getppid();
printf("Abuelo %i \n",getppid());

for(i = 0; i<=5 ; i++)
{	
	pid = fork();
	if(pid==-1){ printf("Tenemos un Error\n");	}
	else if(pid==0) { printf(">> Hijo %i - Proceso %i y Padre %i \n",i, getpid(),padre);}
	a[i]=getpid();
	break;
}

while(1){
if(pid==0)
{
	if(a[0]==getpid())
	{
	  	if(c==0){printf("el proceso %i esta leyendo",getpid()); PonerDatos(); c=1;}
		else if(c==1){printf("Otro proceso esta trabajando :(");}
		sleep(1);
	}

	else if(a[1]==getpid())
	{
	  	
		if(c==0){printf("el proceso %i esta leyendo",getpid()); PonerDatos(); c=1;}
		else if(c==1){printf("Otro proceso esta trabajando :(");}
		sleep(1);
	}

	else if(a[2]==getpid())
	{
	  	
  	if(c==0){printf("se esta leyendo el archivo con el proceso %i.\n",getpid()); VerDatos(); 		c=1;}	
	else if(c==1){printf("Otro proceso esta trabajando :(");}	
		sleep(1);
	}


	else if(a[3]==getpid())
	{
  		if(c==0){printf("se esta leyendo el archivo con el proceso %i.\n",getpid()); VerDatos(); 		c=1;}	
	else if(c==1){printf("Otro proceso esta trabajando :(");}	
		sleep(1);
	}


	else if(a[4]==getpid())
	{
  		if(c==0){printf("se esta leyendo el archivo con el proceso %i.\n",getpid()); VerDatos(); 		c=1;}	
	else if(c==1){printf("Otro proceso esta trabajando :(");}	
		sleep(1);
	}


}	
}
wait(&pid);
return(0);
}

void VerDatos()
{
  char str [80];
  float f;
  FILE * pFile;

  pFile = fopen ("file.txt","w+");
  fprintf (pFile, "%f %s", 3.1416, "PI");
  rewind (pFile);
   fscanf (pFile, "%s", str);
  fclose (pFile);
  printf ("e read: %f and %s \n",f,str);
 
} 

void PonerDatos()
{
   FILE * pFile;
   int n;
   char name [100];

   pFile = fopen ("file.txt","w");
   for (n=0 ; n<3 ; n++)
   {
     
     fprintf (pFile,"%s", "el procesos esta escribiendo");
   }
   fclose (pFile);
   
}


