#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#define num 5;
#define izq (i+num-1)%num;
#define der (i+1)%num
#define pensando 0;
#define hambre 1;
#define comiendo 2;




void * (void * argumento);
void * (void * argumento);
void * (void * argumento);
void * (void * argumento);

sem_t ;
sem_t ;
sem_t ;
sem_t ;

int main()
{       
pthread_t th1,th2,th3,th4;

		sem_init(&,0,0);
		sem_init(&,0,0);
		sem_init(&,0,0);
		sem_init(&,0,0);

		pthread_create(&th1, NULL, , NULL);
		pthread_create(&th2, NULL, , NULL);
		pthread_create(&th3, NULL, , NULL);
		pthread_create(&th4, NULL, , NULL);

        	pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		pthread_join(th3, NULL);
		pthread_join(th4, NULL);
	
		sem_destroy(&s);
		sem_destroy(&);
		sem_destroy(&);	
		sem_destroy(&);

exit(EXIT_FAILURE);
}

void * (void * argumento)
{	
	
}

void * (void * argumento)
{
	
}

void * (void * argumento)
{
	
}

void * (void * argumento)
{	

}
