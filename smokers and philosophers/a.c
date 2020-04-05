#include<stdio.h>
#include<unistd.h>
#include<wait.h>
#include<time.h>
#include <string.h>
#define MAXLINEA 100

int main()
{

int pid,i,b;
int a[10];

char n_arch[] = { "tronco24.txt" };	/* nombre archivo de datos */
char n_arch2[] = { "tronco13.txt" };
char n_prog[] = { "error.txt" };      /* nombre del programa, para error */

char mensaje[] = "";
char linea[MAXLINEA];			/* para lectura */
FILE *p_arch;
FILE *x_arch;                         /* puntero al archivo */

printf("\n----------------------------------------------------------------------------\n");

if ((p_arch = fopen(n_arch, "w")) == NULL) {
	printf("%s: no se puede abrir archivo %s", n_prog, n_arch);
	return 1;			/* error, no pudo abrir el archivo */
}
else {
	fputs(mensaje, p_arch);	/* graba l¡nea en archivo */
 	fclose(p_arch);
}

if ((x_arch = fopen(n_arch2, "w")) == NULL) {
	printf("%s: no se puede abrir archivo %s", n_prog, n_arch2);
	return 1;			/* error, no pudo abrir el archivo */
}
else {
	fputs(mensaje, x_arch);	/* graba l¡nea en archivo */
 	fclose(x_arch);
}



for(i=0;i<=9;i++)
 {
	pid=fork();
	if(pid==-1)
	{printf("error \n");}
	else if(pid==0){
	
	if(i<=3){printf("\n Soy el mono: %i , pid: %i \n",i+1, getpid() ); }
	if(i==4 || i==5) { printf("\n Soy la banana: %i, pid: %i \n", i-3, getpid() ); }
	if(i>5 && i<9) {  printf("\n Soy la rebanada de sandia: %i, pid: %i \n", i-5, getpid() ); }
	if(i==9) {  printf("\n Soy la bolsa de cacahuates: %i, pid: %i \n", i-8, getpid() ); }
	
	a[i]=getpid(); 
	break; }
 }

while(1){ 
	if(pid==0)
	{ 
		if(a[0]==getpid())
		{
	  		x_arch = fopen("//home//alumnos//Documentos//tronco13.txt","r");
	  	
		  	while ( fgets(linea, MAXLINEA, x_arch) != NULL ) 
		  	{
		    		printf("Tronco: %s \n", linea);
		    		if( (strcmp(linea,"libre")) == 0){
			    		x_arch = fopen("//home//alumnos//Documentos//tronco13.txt","w");
			  		strcpy(linea, "ocupado");
			  		fputs(linea, x_arch);
			  		fclose(x_arch);
			    		printf("El mono 1 esta en el tronco"); 
			    	}
		    		else{ printf("Tronco ocupado por el mono 3 \n"); }
		    		}
		  		fclose(x_arch);
				sleep(1);
			}
		}
                	
		if(a[1]==getpid())
		{
	  		p_arch = fopen("//home//alumnos//Documentos//tronco24.txt","r");
		  	while ( fgets(linea, MAXLINEA, p_arch) != NULL ) 
		  	{
		    		printf("Tronco: %s \n", linea);
		    		if( (strcmp(linea,"libre")) == 0){
			    		p_arch = fopen("//home//alumnos//Documentos//tronco24.txt","w");
			  		strcpy(linea, "ocupado");
			  		fputs(linea, p_arch);
			  		fclose(p_arch);
			    		printf("El mono 2 esta en el tronco"); 
			    	}
		    		else{ printf("Tronco ocupado por el mono 4 \n"); }
		    		}
		  		fclose(p_arch);
				sleep(1);
			}
		}

		if(a[2]==getpid())
		{
	  		x_arch = fopen("//home//alumnos//Documentos//tronco13.txt","r");
		  	while ( fgets(linea, MAXLINEA, x_arch) != NULL ) 
		  	{
		    		printf("Tronco: %s \n", linea);
		    		if( (strcmp(linea,"libre")) == 0){
			    		x_arch = fopen("//home//alumnos//Documentos//tronco13.txt","w");
			  		strcpy(linea, "ocupado");
			  		fputs(linea, x_arch);
			  		fclose(x_arch);
			    		printf("El mono 3 esta en el tronco"); 
			    	}
		    		else{ printf("Tronco ocupado por el mono 1 \n"); }
		    		}
		  		fclose(x_arch);
				sleep(1);
			}
		}

		if(a[3]==getpid())
		{
	  		p_arch = fopen("//home//alumnos//Documentos//tronco24.txt","r");
		  	while ( fgets(linea, MAXLINEA, p_arch) != NULL ) 
		  	{
		    		printf("Tronco: %s \n", linea);
		    		if( (strcmp(linea,"libre")) == 0){
			    		p_arch = fopen("//home//alumnos//Documentos//tronco24.txt","w");
			  		strcpy(linea, "ocupado");
			  		fputs(linea, p_arch);
			  		fclose(p_arch);
			    		printf("El mono 4 esta en el tronco"); 
			    	}
		    		else{ printf("Tronco ocupado por el mono 2 \n"); }
		    		}
		  		fclose(p_arch);
				sleep(1);
			}
		}
	}
}
wait(&pid);
return(0);
}





