#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_BUFFER 10/* tamanio del buffer */
#define DATOS_A_PRODUCIR 100 /* datos a producir */
void * Productor(void*a);
void * Consumidor(void*a); /* codigo del Consumidor */

sem_t elementos; /* elementos en el buffer */
sem_t huecos; /* huecos en el buffer */
int buffer[MAX_BUFFER]; /* buffer comun */


int main(void)
{
pthread_t th1, th2; /* identificadores de threads */
	/* inicializar los semaforos */
	sem_init(&elementos, 0, 0);
	sem_init(&huecos, 0, MAX_BUFFER);
	/* crear los procesos ligeros */
	pthread_create(&th1, NULL, Productor, NULL);
	pthread_create(&th2, NULL, Consumidor, NULL);
	/* esperar su finalizacion */
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	/*destrucción de los semaforos*/
	sem_destroy(&huecos);
	sem_destroy(&elementos);
exit(0);
}

void * Productor(void*a) /* codigo del productor */
{
	int pos = 0; /* posicion dentro del buffer */
	int dato,i; /* dato a producir */
	for(i=0; i < DATOS_A_PRODUCIR; i++ ) 
	{
	//dato = i; /* producir dato */
		sem_wait(&huecos); /* un hueco menos */
		buffer[pos] = i;
		printf("dato producido %i \n",buffer[pos]);
		pos = (pos + 1) % MAX_BUFFER;
		sem_post(&elementos); /* un elemento mas */
	}
pthread_exit(0);
}



void * Consumidor(void*a) /* codigo del Consumidor */
{
	int pos = 0;
	int dato,i;
	for(i=0; i < DATOS_A_PRODUCIR; i++ )
	{
		sem_wait(&elementos); /* un elemento menos */
		dato = buffer[pos];
		printf("dato producido %i \n",dato);
		pos = (pos + 1) % MAX_BUFFER;
		sem_post(&huecos); /* un hueco mas */
	}
pthread_exit(0);
}
