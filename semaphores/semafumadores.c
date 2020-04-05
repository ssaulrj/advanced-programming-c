#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

void * cerillo (void * argumento);
void * tabaco (void * argumento);
void * papel (void * argumento);
void * Agente(void * argumento);

sem_t sem;
sem_t sem_fum1;
sem_t sem_fum2;
sem_t sem_fum3;
sem_t sem_agente;

int main()
{       
	pthread_t th1,th2,th3,th4;
		//sem_init(&sem,0,0); //atributo 0 de 1, ultimo 0 es el valor del semaforo
		sem_init(&sem_fum1,0,0);
		sem_init(&sem_fum2,0,0);
		sem_init(&sem_fum3,0,0);
		sem_init(&sem_agente,0,0);
 	
		pthread_create(&th1, NULL, Agente, NULL);
		pthread_create(&th2, NULL, tabaco, NULL);
		pthread_create(&th3, NULL, cerillo, NULL);
		pthread_create(&th4, NULL, papel, NULL);

        	pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		pthread_join(th3, NULL);
		pthread_join(th4, NULL);
	
		sem_destroy(&sem_fum1);
		sem_destroy(&sem_fum2);
		sem_destroy(&sem_fum3);	
		sem_destroy(&sem_agente);
	exit(EXIT_FAILURE);
}

void * cerillo(void * argumento)
{	
	while(1)
	{	
		sem_wait(&sem_fum1);
		printf("- Fumador 1 con cerillo -\n");
		printf("- Cerillo  -\n\n");
		sem_post(&sem_agente);
	}
}

void * tabaco(void * argumento)
{
	while(1)
	{	
		sem_wait(&sem_fum2);
		printf("- Fumador 2 con tabaco -\n");
		printf("- Tabaco -\n\n");
		sem_post(&sem_agente);
	}
}

void * papel(void * argumento)
{
	while(1)
	{		
		sem_wait(&sem_fum3);
		printf("- Fumador 3 que tienen papel, preparando cigarro -\n");
		printf("- Papel - \n\n");
		sem_post(&sem_agente);
	}
}

void * Agente(void * argumento)
{	int ing1;
	int ing2;
	//sem_wait(&sem_agente);
	//printf("entre a agente");
	while(1)
	{
		do
		{
		ing1= rand()%3; 
		ing2= rand()%3;
	
		} while(ing1==ing2);
		
		printf("1 y 2 Fumador con cerillo - 0 y 2 Fumador con tabaco - 0 y 1 Fumador con papel \n");
	        printf("Rand 1: %i, Rand 2: %i \n", ing1, ing2);
		
		if((ing1==0 && ing2==1)||(ing1==1 && ing2==0))
		{
			sem_post(&sem_fum3);
			sem_wait(&sem_agente);
		}
		if((ing1==0 && ing2==2)||(ing1==2 && ing2==0))
		{
			sem_post(&sem_fum2);
			sem_wait(&sem_agente);
		}
		if((ing1==1 && ing2==2)||(ing1==2 && ing2==1))
		{
			sem_post(&sem_fum1);
			sem_wait(&sem_agente);
		}
	}
}
