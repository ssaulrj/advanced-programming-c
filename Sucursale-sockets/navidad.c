#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define n_renos 7 
#define n_duendes 3
#define vacaciones 0
#define durmiendo 1
#define comida 2
#define enforma 3
#define trineo 10
int c=0;
//--------duendes
void *funcion_duendes(void *j);
void recibir_cartas(int);
void formar_equipos(int);
void llenar_trineo(int);
int d_num[n_duendes]={0,1,2};
int aux_trineo=0;
//--------renos 
void *funcion_reno(void *i);
void free_time(int);
void prepararse(int);
void r_bitacora(int);
void esperar(int);
void ready();
int ren_num[n_renos]={0,1,2,3,4,5,6};
//-------------
//--------funciones de papa noel
void *funcion_pn();
void duende_despierta();
void avisar_reno();
void entregar_regalos();
//------------------------------
//pid para papa noel y el reno
int pid;
int pid1;
int pipe_pn_r[2];
int pipe_r_pn[2];
char mensaje_pn_r[50];
char mensaje_r_pn[50];
//-------------------------------
int aux1=0;
//pid para los duendes
int pid1;
int pipe_duendes[2];
char mensaje_duende1[50];
//-----------mutex para saber que los renos ya estan listos 
pthread_mutex_t mutex_renos = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
//-----------mutex para el trineo
pthread_mutex_t mutex_trineo = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_trineo = PTHREAD_COND_INITIALIZER;
//-----------mutex para el mensaje deel duende 1 al 2
pthread_mutex_t mutex_men = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cv_men = PTHREAD_MUTEX_INITIALIZER;
//----------
//pid para comunicar a duende 3 a papa noel
int pid2;
int pipe_santa[2];
char mensaje_d3_s[50];
int a=0;
int main(int argc, char *argv[]) {
	int i;
	int j;
	pipe(pipe_pn_r);
	pipe(pipe_r_pn);

	pipe(pipe_duendes);

	pipe(pipe_santa);

	pthread_t renos[n_renos];
	pthread_t papa_noel;
	pthread_t duendes[n_duendes];
		
	for(j=0 ; j<n_duendes ; j++){
        pthread_create(&duendes[j],NULL,funcion_duendes,&d_num[j]);
        printf("Creacion del duende(lider) %d \n",j+1);
        }
	
	pthread_create(&papa_noel,NULL,funcion_pn,NULL);

	for(i=0 ; i<n_renos ; i++){
        pthread_create(&renos[i],NULL,funcion_reno,&ren_num[i]);
        printf("Creacion del reno(hilo) %d \n",i+1);
        }

	pthread_join(papa_noel,NULL);

	for (i=0 ; i<n_renos ; i++){
	pthread_join(renos[i],NULL);
	}
	for (j=0 ; j<n_duendes ; j++){
	pthread_join(duendes[j],NULL);
	}
	return 0;
}
//---------------------------------------------duendes

//---------------------------------------------papa noel
void *funcion_pn(){
sleep(2);
duende_despierta();
avisar_reno();
entregar_regalos();
}
void duende_despierta(){
read(pipe_santa[0],mensaje_d3_s,strlen(mensaje_d3_s)+1);
printf("El duende 3 me %s",mensaje_d3_s);
}
void avisar_reno(){
printf("Avisando al reno 007\n");
if( (pid=fork()) != 0 ){
strcpy(mensaje_pn_r,"Despierta a los demas renos\n");
write(pipe_pn_r[1],mensaje_pn_r,strlen(mensaje_pn_r)+1);
read(pipe_r_pn[0],mensaje_r_pn,50);
printf("Mensaje de los renos: %s\n",mensaje_r_pn);
}

}

void entregar_regalos(){
printf("Vamos a entregar regalos\n");
}

//-------------------------------------------renos 
void *funcion_reno(void *i){
int *aux=i;
free_time(*aux);
prepararse(*aux);
r_bitacora(*aux);
esperar(*aux);	
ready(*aux);
}

void free_time(int x){
switch(rand()%2){
	case vacaciones:
		printf("Reno %d esta de vacciones\n",x);
		break;
	case durmiendo:
		printf("Reno %d esta durmiendo\n",x);
		break;	
}	
}

void prepararse(int x){
int y;
y= 2 + rand() % (4-2);	
switch(y){
	case comida:
		printf("Reno %d esta comiendo\n",x);
		break;
	case enforma:
		printf("Reno %d esta en forma\n",x);
		break;	
}	
}

void r_bitacora(int x){
printf("El reno  %d se registro en la bitacora de llegada\n",x);	
}	

void esperar(int x){
pthread_mutex_lock(&mutex_renos);
printf("El reno  %d va a esperar el 25 de dicimebre \n",x);
aux1++;
pthread_mutex_unlock(&mutex_renos);
pthread_cond_signal(&cv);
}

void ready(int x){	
int done=0;
sleep(3); 		//esperamos medio año
	while(!done)
	{
		pthread_mutex_lock(&mutex_renos);
		while(aux1<6)
		{
			pthread_cond_wait(&cv,&mutex_renos);
		}
		done=1;	
		pthread_mutex_unlock(&mutex_renos);	
		//printf("Sali---------\n");
	}

	/* no se*/
	if( (pid=fork())==0 ){
	read(pipe_pn_r[0],mensaje_pn_r,50);	
	printf("Reno 007 avisado\n");
	printf("Mensaje Recibido %s\n",mensaje_pn_r);
	strcpy(mensaje_r_pn,"READY!!!\n");
	write(pipe_r_pn[1],mensaje_r_pn,strlen(mensaje_r_pn)+1);
	}
	
}

//------------------------------------------duendes
void *funcion_duendes(void *j){
int *aux2=j; 
while(!c){
recibir_cartas(*aux2);
formar_equipos(*aux2);
llenar_trineo(*aux2);
}

}
void recibir_cartas(int t){
int random= rand() % 4;
	if(t==0){
	switch(random){
	case 0:
	pthread_mutex_lock(&mutex_men);
	printf("Duende %d (lider) recibio una carta pidiendo un coche\n",t+1);
	strcpy(mensaje_duende1,"coc");
	write(pipe_duendes[1],mensaje_duende1,strlen(mensaje_duende1)+1);
	pthread_mutex_unlock(&mutex_men);
	break;
	case 1:
	pthread_mutex_lock(&mutex_men);
	printf("Duende %d (lider) recibio una carta pidiendo una muñeca\n",t+1);
	strcpy(mensaje_duende1,"mun");
	write(pipe_duendes[1],mensaje_duende1,strlen(mensaje_duende1)+1);	
	pthread_mutex_unlock(&mutex_men);
	break;
	case 2:
	pthread_mutex_lock(&mutex_men);
	printf("Duende %d (lider) recibio una carta pidiendo una pelota \n",t+1);
	strcpy(mensaje_duende1,"pel");
	write(pipe_duendes[1],mensaje_duende1,strlen(mensaje_duende1)+1);	
	pthread_mutex_unlock(&mutex_men);
	break;
	case 3:
	pthread_mutex_lock(&mutex_men);
	printf("Duende %d (lider) recibio una carta pidiendo un yoyo\n",t+1);
	strcpy(mensaje_duende1,"yoy");
	write(pipe_duendes[1],mensaje_duende1,strlen(mensaje_duende1)+1);
	pthread_mutex_unlock(&mutex_men);	
	break;
	}
	}
	
}
void formar_equipos(int t){
if(t==1){
	printf("--------%d--------\n",strlen(mensaje_duende1));
	printf("--Duende 2(lider) formando equipos\n");
	read(pipe_duendes[0],mensaje_duende1,strlen(mensaje_duende1)+1);	
	printf("Duende 1 materiales para el juguete %s\n",mensaje_duende1);
	printf("Duende 2 arma el juguete %s\n",mensaje_duende1);
	printf("Duende 3 pinta y empaca el juguete %s\n",mensaje_duende1);
	
	pthread_mutex_lock(&mutex_trineo);
	aux_trineo++;
	pthread_mutex_unlock(&mutex_trineo);
	pthread_cond_signal(&cv_trineo);
}
}
void llenar_trineo(int t){
	pthread_mutex_lock(&mutex_trineo);
	if(aux_trineo==trineo){
	printf("Duende 3(lider)\n");
	printf("El trineo esta lleno\n");
	c=1; //detenemos a todos los duendes lideres de su labor
	
	
	//avisar a papa noel
	printf("el trineo esta lleno avisando a santa\n");
	strcpy(mensaje_d3_s,"levanta\n");
	write(pipe_santa[1],mensaje_d3_s,strlen(mensaje_d3_s)+1);

	}	
	pthread_mutex_unlock(&mutex_trineo);
	pthread_cond_signal(&cv_trineo);
		
	

}












































