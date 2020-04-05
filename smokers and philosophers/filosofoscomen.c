#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <pthread.h>
#include <semaphore.h>
#include<time.h> 

//int n=5;

int estado[5];
pthread_t filos[5];
sem_t filosofos[5];
sem_t semtene,semjarra; 

void* comensales(int i);
void tomarcubiertos(int i);
void dejarcubiertos(int i);
void tomaragua(int i);
void verificarcubiertos (int i);
void verificarjarra(int i);

void main(){
int j;

for(j=0;j<5;j++){
   sem_init(&filosofos[j],0,1);
   estado[j]=0;
		}

for(j=0;j<5;j++){
   pthread_create(&filos[j],NULL,(void*)comensales,(void*)(j+1));
		}

for(j=0;j<5;j++){
   pthread_join(filos[j],NULL);
		}

for(j=0;j<5;j++){
   sem_destroy(&filosofos[j]);
		}



	    }

void*  comensales(int i){
 while(1){
     printf(" filosofo %d esta pensando\n",i);
     tomarcubiertos(i);
     dejarcubiertos( i);
     sleep(5);
}
}
void tomarcubiertos(int i)
{
  
  //sem_wait(&semtene); 
 
  estado[i] = 1;      
  verificarcubiertos(i);                 
  sem_post(&semtene);           
  sem_wait(&filosofos[i]);   
            
}
void dejarcubiertos(int i)
{
  
  sem_wait(&semtene);      
  estado[i] =0;  //deja de comer y se pone a pensar
  verificarcubiertos((i-1)%5);        
  verificarcubiertos((i+1)%5);
  sem_post(&semtene);
}

void tomarjarra(int i){
  //sem_wait(&semjarra);             
  estado[i] = 3;      //3tengosed 4tomando agua
  verificarjarra(i);                 
  sem_post(&semjarra);           
  sem_wait(&filosofos[i]);

}
void verificarcubiertos(int i){
 if( estado[i]==1 && estado[i-1]!=2 && estado[i+1]!=2 ){
    estado[i] =2;
    printf("Filosofo %d comiendo\n", i) ;
    sem_post(&filosofos[i]);
  }
  else{
   estado[i] = 3;      
  verificarjarra(i);                 
  sem_post(&semjarra);           
  sem_wait(&filosofos[i]);            
  
  }

			 }

void verificarjarra(int i){
   if( estado[i]==3 && estado[i-1]!=4 && estado[i+1]!=4 ){
    estado[i] =4;
    printf("Filosofo %d sirviendo agua\n", i) ;
    sem_post(&filosofos[i]);
  }
  else{
  printf("el filosofo %i no puede tomar agua porque la jarra esta coupada\n",i);
  }
}

