#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void * funcion_hilo (void * argumento);
char mensaje[]="					---Hola hilo---";
int contador=0;
int i=0;

int main()
{
	pthread_t id_hilo[5];
	void * valor_retorno;

		for(int sumah=0;sumah<=4;sumah++)
		{
			if(pthread_create(&id_hilo[sumah], NULL, funcion_hilo, (void*)mensaje))
			{ 	printf("-Problema en la creacion del hilo -\n");
				exit(EXIT_FAILURE); 
			}
		}

	printf("-Esperando a que termine el hilo hijos... -\n");
		
		for(int joinh=0;joinh<=4;joinh++)
		{
			if(pthread_join(id_hilo[joinh], & valor_retorno))
			{	printf("-Problema al crear enlace con otro hilo 'n'-\n");
				exit(EXIT_FAILURE);
			}
		}
		 	
	while(1)
	{
		printf("Id del hilo 1 -- %d , valor: %i \n", id_hilo[0],  contador=contador+1);
		sleep(1);
		printf("Id del hilo 2 -- %d , valor: %i \n", id_hilo[1],  contador=contador+2);
		sleep(1);
		printf("Id del hilo 3 -- %d , valor: %i \n", id_hilo[2],  contador=contador+3);
		sleep(1);
		printf("Id del hilo 4 -- %d , valor: %i \n", id_hilo[3],  contador=contador+4);
		sleep(1);
		printf("Id del hilo 5 -- %d , valor: %i \n", id_hilo[4],  contador=contador+5);
		sleep(1);	
	}

	printf("\n\n-Los hilos que esperamos, regresaron!, Numero es:  \t %s -\n",(char *)valor_retorno);
	printf("-Nuevo mensaje: %s \n", mensaje);
	exit(EXIT_FAILURE);
}

void * funcion_hilo (void * argumento)
{       
	pthread_t pid= pthread_self(); 
	printf("-Numero id de hilo- %i \n", pid );
	printf("	*El codigo de la funcion esta en ejecucion* \n -El argumento es: %s \n",(char *)argumento );
	sleep(2);
	strcpy(mensaje, "-Adios!-");
	pthread_exit("\n -Gracias por el tiempo CPU-"); 
}


//imprima hilo en cual esta implementando y vairable global,   
// pthread_self() = getpid(); 
