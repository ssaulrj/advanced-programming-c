#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <semaphore.h>
#include <wait.h>
#define MAX 100


void *Empaquetar();
void *recibir_paquete();
void *recibir_paqueteb();
void *Enviar();
int gana=0;

int pid_mos1;
int pid_mos2;
int pid_mos3;
int pipe_mos[3];

char mensaje[60];
//tuberias
char mensaje_costo1[MAX];
char mensaje_dim1[MAX];
char mensaje_peso1[MAX];
char pipe_mostrac1[3];
char pipe_mostrad1[3];
char pipe_mostrap1[3];


char mensaje_costo2[MAX];
char mensaje_dim2[MAX];
char mensaje_peso2[MAX];
char pipe_mostrac2[3];
char pipe_mostrad2[3];
char pipe_mostrap2[3];


char mensaje_costo3[MAX];
char mensaje_dim3[MAX];
char mensaje_peso3[MAX];
char pipe_mostrac3[3];
char pipe_mostrad3[3];
char pipe_mostrap3[3];
//Hilos 



//mutex para mostradores
pthread_mutex_t mutex_mostra1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_mostra2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_mostra3 = PTHREAD_MUTEX_INITIALIZER;

//mutex de tienda
pthread_mutex_t mutex_tiendaa = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_tiendab = PTHREAD_MUTEX_INITIALIZER;

//mutex para empacadores
pthread_mutex_t mutex_empacador1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_empacador2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_empacador3 = PTHREAD_MUTEX_INITIALIZER;

//mutex de repartidores
pthread_mutex_t mutex_repartidor1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_repartidor2 = PTHREAD_MUTEX_INITIALIZER;



//pid de empar
int pid_em1;
int pid_em2;
int pid_em3;
int pipe_em[3];
char mensaje2[60];

//pid de gerente gerenal 
int pid_ge;
int pipe_ge[1];
char mensaje3[60];





int main(int arg,char *argv[])

{
    
    int identificador;
    int x;
    pthread_t mostradort;
    pthread_t empacadort;
    pthread_t mensajerot;
pthread_t mostradortt;
    
    pthread_create(&mostradort,NULL,&recibir_paquete,NULL);
    pthread_create(&mostradortt,NULL,&recibir_paqueteb,NULL);
    pthread_create(&empacadort,NULL,&Empaquetar,NULL);
    pthread_create(&mensajerot,NULL,&Enviar,NULL );
do{	
srand(time(NULL));
int random= rand() % 2;
switch(random)
{
case 0:
pthread_mutex_lock(&mutex_tiendaa);
recibir_paquete();
printf("Esta en la tienda A");
identificador=1;
pthread_mutex_unlock(&mutex_tiendaa);
pthread_exit(0);
break;
case 1:
pthread_mutex_lock(&mutex_tiendab);
recibir_paqueteb();
printf("Esta en la tienda B");
identificador=2;
pthread_mutex_unlock(&mutex_tiendab);
pthread_exit(0);
break;
}

}while(1);
}



int nota(int pe,int dim,int cos)
{
    FILE *archivo;
    int con=0;
    
    archivo = fopen("HistorialA.txt", "w+");

    con=con+1;
    gana=gana+cos;
    printf("El paquete se esta archivando");
    fprintf(archivo,"El paquete %i ha llegado con los siguientes datos \n",con);
    fprintf(archivo,"Peso: %i \n Dimension: %i cm^2\n Costo: $ %i  ",pe,dim,cos);
    fprintf(archivo,"\nLa ganancia al momento es de: %i",gana);
    fclose(archivo);
    return (con);


}

int notab(int pe,int dim,int cos)
{
    FILE *archivo;
    int con=0;
    
    archivo = fopen("HistorialB.txt", "w+");

    con=con+1;
    gana=gana+cos;
    printf("El paquete se esta archivando");
    fprintf(archivo,"El paquete %i ha llegado con los siguientes datos \n",con);
    fprintf(archivo,"Peso: %i \n Dimension: %i cm^2\n Costo: $ %i  ",pe,dim,cos);
    fprintf(archivo,"\nLa ganancia al momento es de: %i",gana);
    fclose(archivo);
    return (con);


}


void *Enviar()
{

     
}




void *Empaquetar()

{
int pe,dim,costo;
int pid,i;
int e[3];
int abrirp;
int abrirc;
int abrird;

for(i=1;i<=3;i++)
	{
		pid=fork();
		if(pid==-1)
		{printf("error \n");}
		else if(pid==0)
		{
		
		e[i]=getpid(); 
		
		break;
		}

	}


	if (pid==0)
	{

mknod(pipe_mostrad1,S_IFIFO|0666,0);
mknod(pipe_mostrap1,S_IFIFO|0666,0);
mknod(pipe_mostrac1,S_IFIFO|0666,0);

mknod(pipe_mostrad2,S_IFIFO|0666,0);
mknod(pipe_mostrap2,S_IFIFO|0666,0);
mknod(pipe_mostrac2,S_IFIFO|0666,0);

mknod(pipe_mostrad3,S_IFIFO|0666,0);
mknod(pipe_mostrap3,S_IFIFO|0666,0);
mknod(pipe_mostrac3,S_IFIFO|0666,0);



		if(e[1]==getpid())
			{
			pthread_mutex_lock(&mutex_empacador1);
			printf("\nEsta con el empaquetador numero %i con identificador %i que empaquetara %i\n",i,getpid());
			pe = 3 + rand () % (11-3);
			abrirp=open(pipe_mostrap1,O_WRONLY);
			strcpy(mensaje_peso1,"\nEl peso es:"+pe);			
			write(abrirp,mensaje_peso1,strlen(mensaje_peso1)+1);			
			//write(pipe_mostrap1[1],mensaje_peso1,pe);
			close(abrirp);
			exit(0);			

			dim = 2 + rand () % (7-2);
			abrird=open(pipe_mostrad1,O_WRONLY);
			strcpy(mensaje_dim1,"\nLa dimension es"+dim);
			write(abrird,mensaje_dim1,strlen(mensaje_dim1)+1);
			close(abrird);
			exit(0);
		
			costo = 50 + rand () % (301-50);
			abrirc=open(pipe_mostrac1,O_WRONLY);
			strcpy(mensaje_costo1,"\nEl costo es:"+costo);
			write(abrirc,mensaje_costo1,strlen(mensaje_costo1)+1);
			nota(pe,dim,costo);
			close(abrirc);
			exit(0);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
					
			pthread_mutex_unlock(&mutex_empacador1);
			pthread_exit(0);
			}
			if(e[2]==getpid())
			{
			pthread_mutex_lock(&mutex_empacador2);
			printf("\nEsta con el empaquetador numero %i con identificador %i que empaquetara %i\n",i,getpid());
			
			pe = 3 + rand () % (11-3);
			abrirp=open(pipe_mostrap2,O_WRONLY);
			strcpy(mensaje_peso2,"\nEl peso es:"+pe);			
			write(abrirp,mensaje_peso2,strlen(mensaje_peso2)+1);
			abrirp=open(pipe_mostrap2,O_WRONLY);			
			//write(pipe_mostrap2[1],mensaje_peso2);
			close(abrirp);
			exit(0);			

			dim = 2 + rand () % (7-2);
			abrird=open(pipe_mostrad2,O_WRONLY);
			strcpy(mensaje_dim2,"\nLa dimension es"+dim);
			write(abrird,mensaje_dim2,strlen(mensaje_dim2)+1);
			close(abrird);
			exit(0);
		
			costo = 50 + rand () % (301-50);
			abrirc=open(pipe_mostrac2,O_WRONLY);
			strcpy(mensaje_costo2,"\nEl costo es:"+costo);
			write(abrirc,mensaje_costo2,strlen(mensaje_costo2)+1);
			
			nota(pe,dim,costo);
			close(abrirc);
			exit(0);
			pthread_mutex_unlock(&mutex_empacador2);
			pthread_exit(0);

			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
			}

		if(e[3]==getpid())
			{
			pthread_mutex_lock(&mutex_empacador3);
			printf("\nEsta con el empaquetador numero %i con identificador %i que empaquetara %i\n",i,getpid());
			pe = 3 + rand () % (11-3);
			
			abrirp=open(pipe_mostrap3,O_WRONLY);
			strcpy(mensaje_peso3,"El peso es:"+pe);				
			write(abrirp,mensaje_peso3,strlen(mensaje_peso3)+1);
					
			//write(pipe_mostrap3[1],mensaje_peso3);
			close(abrirp);
			exit(0);			

			dim = 2 + rand () % (7-2);
			abrird=open(pipe_mostrad3,O_WRONLY);
			strcpy(mensaje_dim3,"\nLa dimension es"+dim);
			write(abrird,mensaje_dim3,strlen(mensaje_dim3)+1);
			close(abrird);
			exit(0);
		
			costo = 50 + rand () % (301-50);
			abrirc=open(pipe_mostrac3,O_WRONLY);
			strcpy(mensaje_costo3,"\nEl costo es:"+costo);
			write(abrirc,mensaje_costo3,strlen(mensaje_costo3)+1);
			nota(pe,dim,costo);
			close(abrirc);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
			exit(0);
			pthread_mutex_unlock(&mutex_empacador3);
			pthread_exit(0);
			}


	}






}


void *Empaquetarb()

{
int pe,dim,costo;
int pid,i;
int e[3];
int abrirp;
int abrirc;
int abrird;

for(i=1;i<=3;i++)
	{
		pid=fork();
		if(pid==-1)
		{printf("error \n");}
		else if(pid==0)
		{
		
		e[i]=getpid(); 
		
		break;
		}

	}


	if (pid==0)
	{

mknod(pipe_mostrad1,S_IFIFO|0666,0);
mknod(pipe_mostrap1,S_IFIFO|0666,0);
mknod(pipe_mostrac1,S_IFIFO|0666,0);

mknod(pipe_mostrad2,S_IFIFO|0666,0);
mknod(pipe_mostrap2,S_IFIFO|0666,0);
mknod(pipe_mostrac2,S_IFIFO|0666,0);

mknod(pipe_mostrad3,S_IFIFO|0666,0);
mknod(pipe_mostrap3,S_IFIFO|0666,0);
mknod(pipe_mostrac3,S_IFIFO|0666,0);



		if(e[1]==getpid())
			{
			pthread_mutex_lock(&mutex_empacador1);
			printf("\nEsta con el empaquetador numero %i con identificador %i que empaquetara %i\n",i,getpid());
			pe = 3 + rand () % (11-3);
			abrirp=open(pipe_mostrap1,O_WRONLY);
			strcpy(mensaje_peso1,"\nEl peso es:"+pe);			
			write(abrirp,mensaje_peso1,strlen(mensaje_peso1)+1);			
			//write(pipe_mostrap1[1],mensaje_peso1,pe);
			close(abrirp);
			exit(0);			

			dim = 2 + rand () % (7-2);
			abrird=open(pipe_mostrad1,O_WRONLY);
			strcpy(mensaje_dim1,"\nLa dimension es"+dim);
			write(abrird,mensaje_dim1,strlen(mensaje_dim1)+1);
			close(abrird);
			exit(0);
		
			costo = 50 + rand () % (301-50);
			abrirc=open(pipe_mostrac1,O_WRONLY);
			strcpy(mensaje_costo1,"\nEl costo es:"+costo);
			write(abrirc,mensaje_costo1,strlen(mensaje_costo1)+1);
			nota(pe,dim,costo);
			close(abrirc);
			exit(0);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
					
			pthread_mutex_unlock(&mutex_empacador1);
			pthread_exit(0);
			}
			if(e[2]==getpid())
			{
			pthread_mutex_lock(&mutex_empacador2);
			printf("\nEsta con el empaquetador numero %i con identificador %i que empaquetara %i\n",i,getpid());
			
			pe = 3 + rand () % (11-3);
			abrirp=open(pipe_mostrap2,O_WRONLY);
			strcpy(mensaje_peso2,"\nEl peso es:"+pe);			
			write(abrirp,mensaje_peso2,strlen(mensaje_peso2)+1);
			abrirp=open(pipe_mostrap2,O_WRONLY);			
			//write(pipe_mostrap2[1],mensaje_peso2);
			close(abrirp);
			exit(0);			

			dim = 2 + rand () % (7-2);
			abrird=open(pipe_mostrad2,O_WRONLY);
			strcpy(mensaje_dim2,"\nLa dimension es"+dim);
			write(abrird,mensaje_dim2,strlen(mensaje_dim2)+1);
			close(abrird);
			exit(0);
		
			costo = 50 + rand () % (301-50);
			abrirc=open(pipe_mostrac2,O_WRONLY);
			strcpy(mensaje_costo2,"\nEl costo es:"+costo);
			write(abrirc,mensaje_costo2,strlen(mensaje_costo2)+1);
			
			nota(pe,dim,costo);
			close(abrirc);
			exit(0);
			pthread_mutex_unlock(&mutex_empacador2);
			pthread_exit(0);

			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
			}

		if(e[3]==getpid())
			{
			pthread_mutex_lock(&mutex_empacador3);
			printf("\nEsta con el empaquetador numero %i con identificador %i que empaquetara %i\n",i,getpid());
			pe = 3 + rand () % (11-3);
			
			abrirp=open(pipe_mostrap3,O_WRONLY);
			strcpy(mensaje_peso3,"El peso es:"+pe);				
			write(abrirp,mensaje_peso3,strlen(mensaje_peso3)+1);

					
			//write(pipe_mostrap3[1],mensaje_peso3);
			close(abrirp);
			exit(0);			

			dim = 2 + rand () % (7-2);
			abrird=open(pipe_mostrad3,O_WRONLY);
			strcpy(mensaje_dim3,"\nLa dimension es"+dim);
			write(abrird,mensaje_dim3,strlen(mensaje_dim3)+1);
			close(abrird);
			exit(0);
		
			costo = 50 + rand () % (301-50);
			abrirc=open(pipe_mostrac3,O_WRONLY);
			strcpy(mensaje_costo3,"\nEl costo es:"+costo);
			write(abrirc,mensaje_costo3,strlen(mensaje_costo3)+1);
			nota(pe,dim,costo);
			close(abrirc);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
			exit(0);
			pthread_mutex_unlock(&mutex_empacador3);
			pthread_exit(0);
			}


	}






}


void *recibir_paquete(void *arg)
{
int pid,i;
int m[3];
int pe,dim,costo;
int abrirp;
int abrirc;
int abrird;
printf("\nEsta en la tienda  A    \n");
for(i=1;i<=3;i++)
 	{
	pid=fork();
	if(pid==-1)
		{
		printf("error \n");}
		else if(pid==0){
		m[i]=getpid(); 
		break;
		}
 	}
	
if(pid==0)
{
	if(m[1]==getpid())
	{
    pthread_mutex_lock(&mutex_mostra1); 
	printf("\nEsta con el empleado numero %i con identificador %i que verificara si el paquete esta corecto\n",i,getpid());
	srand(time(NULL));
	int random= rand() % 2;
	printf("\nrandom:%i\n",random);
		switch(random)
		{
		case 0:
		printf("\nEl paquete esta correcto");
		pe = 3 + rand () % (11-3);	
		dim = 2 + rand () % (7-2);
		costo = 50 + rand () % (301-50);
		nota(pe,dim,costo);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
		
		//desbloqueo a el empleado1
		break;
		//caso para enviar  a empaquetar y recibir los datos del paquete
		case 1:
		printf("\nEl paquete esta mal empaquetado");
		Empaquetar();
		abrirp=open(pipe_mostrap1,O_RDONLY);
		read(abrirp,mensaje_peso1,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad1,O_RDONLY);
		read(abrird,mensaje_dim1,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac1,O_RDONLY);
		read(abrirc,mensaje_costo1,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap2,O_RDONLY);
		read(abrirp,mensaje_peso2,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad2,O_RDONLY);
		read(abrird,mensaje_dim2,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac2,O_RDONLY);
		strcpy(mensaje_costo2,"\nEl costo es:"+costo);
		read(abrirc,mensaje_costo2,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap3,O_RDONLY);
		read(abrirp,mensaje_peso3,MAX);
				
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad3,O_RDONLY);
		read(abrird,mensaje_dim3,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac3,O_RDONLY);
		strcpy(mensaje_costo3,"\nEl costo es:"+costo);
		read(abrirc,mensaje_costo3,MAX);
		close(abrirc);
		exit(0);
		

		
		break;
		}

	sleep(2);
	pthread_mutex_unlock(&mutex_mostra1);
	pthread_exit(0);
	}
	



	if(m[2]==getpid())
	{
	pthread_mutex_lock(&mutex_mostra2);
	printf("\nEsta con el empleado numero %i con identificador %i que verificara si el paquete esta corecto \n",i,getpid());
	int random= rand() % 2;
	srand(time(NULL));
	printf("\nrandom:%i",random);
		switch(random)
		{
		case 0:
		printf("\nEl paquete esta correcto\n");
		pe = 3 + rand () % (11-3);	
		dim = 2 + rand () % (7-2);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
		costo = 50 + rand () % (301-50);			

		nota(pe,dim,costo);
		//desbloqueo a el empleado2
		break;
		
		case 1:
		printf("\nEl paquete esta mal empaquetado\n");
		Empaquetar();
	
		abrirp=open(pipe_mostrap1,O_RDONLY);
		read(abrirp,mensaje_peso1,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad1,O_RDONLY);
		read(abrird,mensaje_dim1,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac1,O_RDONLY);
		strcpy(mensaje_costo1,"El costo es:"+costo);
		read(abrirc,mensaje_costo1,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap2,O_RDONLY);
		read(abrirp,mensaje_peso2,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad2,O_RDONLY);
		read(abrird,mensaje_dim2,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac2,O_RDONLY);
		read(abrirc,mensaje_costo2,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap3,O_RDONLY);
		read(abrirp,mensaje_peso3,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad3,O_RDONLY);
		read(abrird,mensaje_dim3,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac3,O_RDONLY);
		read(abrirc,mensaje_costo3,MAX);
		close(abrirc);
		exit(0);
		break;
		}

	sleep(2);
	pthread_mutex_unlock(&mutex_mostra2);
	pthread_exit(0);
	}
	



	if(m[3]==getpid())
	{
    pthread_mutex_lock(&mutex_mostra3); 
	printf("\nEsta con el empleado numero %i con identificador %i que verificara si el paquete esta corecto \n",i,getpid());
	srand(time(NULL));
	int random= rand() % 3;
	printf("\nrandom:%i",random);
		switch(random)
		{
		case 0:
		printf("\nEl paquete esta correcto");
		pe = 3 + rand () % (11-3);	
		dim = 2 + rand () % (7-2);
		costo = 50 + rand () % (301-50);
		nota(pe,dim,costo);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
		//desbloqueo a el empleado3
		break;
		
		case 1:
		printf("\nEl paquete esta mal empaquetado");
		Empaquetar();

		abrirp=open(pipe_mostrap1,O_RDONLY);
		read(abrirp,mensaje_peso1,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad1,O_RDONLY);
		read(abrird,mensaje_dim1,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac1,O_RDONLY);
		read(abrirc,mensaje_costo1,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap2,O_RDONLY);
		read(abrirp,mensaje_peso2,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad2,O_RDONLY);
		read(abrird,mensaje_dim2,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac2,O_RDONLY);
		read(abrirc,mensaje_costo2,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap3,O_RDONLY);
		read(abrirp,mensaje_peso3,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad3,O_RDONLY);
		read(abrird,mensaje_dim3,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac3,O_RDONLY);
		read(abrirc,mensaje_costo3,MAX);
		close(abrirc);
		exit(0);
		break;
		}

	sleep(2);
	pthread_mutex_unlock(&mutex_mostra3);
	pthread_exit(0);
	}
	
}	
wait(&pid);


}

void *recibir_paqueteb(void *arg)
{
int pid,i;
int m[3];
int pe,dim,costo;
int abrirp;
int abrirc;
int abrird;
printf("Esta en la tienda B");
for(i=1;i<=3;i++)
 	{
	pid=fork();
	if(pid==-1)
		{
		printf("error \n");}
		else if(pid==0){
		m[i]=getpid(); 
		break;
		}
 	}
	
if(pid==0)
{
	if(m[1]==getpid())
	{
    pthread_mutex_lock(&mutex_mostra1); 
printf("Tienda B");
	printf("\nEsta con el empleado numero %i con identificador %i que verificara si el paquete esta corecto\n",i,getpid());
	srand(time(NULL));
	int random= rand() % 2;
	printf("\nrandom:%i\n",random);
		switch(random)
		{
		case 0:
		printf("\nEl paquete esta correcto tienda b");
		pe = 3 + rand () % (11-3);	
		dim = 2 + rand () % (7-2);
		costo = 50 + rand () % (301-50);
		notab(pe,dim,costo);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
		
		//desbloqueo a el empleado1
		break;
		//caso para enviar  a empaquetar y recibir los datos del paquete
		case 1:
		printf("\nEl paquete esta mal empaquetado");
		Empaquetarb();
		abrirp=open(pipe_mostrap1,O_RDONLY);
		read(abrirp,mensaje_peso1,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad1,O_RDONLY);
		read(abrird,mensaje_dim1,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac1,O_RDONLY);
		read(abrirc,mensaje_costo1,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap2,O_RDONLY);
		read(abrirp,mensaje_peso2,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad2,O_RDONLY);
		read(abrird,mensaje_dim2,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac2,O_RDONLY);
		strcpy(mensaje_costo2,"\nEl costo es:"+costo);
		read(abrirc,mensaje_costo2,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap3,O_RDONLY);
		read(abrirp,mensaje_peso3,MAX);
				
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad3,O_RDONLY);
		read(abrird,mensaje_dim3,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac3,O_RDONLY);
		strcpy(mensaje_costo3,"\nEl costo es:"+costo);
		read(abrirc,mensaje_costo3,MAX);
		close(abrirc);
		exit(0);
		

		
		break;
		}

	sleep(2);
	pthread_mutex_unlock(&mutex_mostra1);
	pthread_exit(0);
	}
	



	if(m[2]==getpid())
	{
	pthread_mutex_lock(&mutex_mostra2);
	printf("\nEsta con el empleado numero %i con identificador %i que verificara si el paquete esta corecto \n",i,getpid());
	int random= rand() % 2;
	srand(time(NULL));
	printf("\nrandom:%i",random);
		switch(random)
		{
		case 0:
		printf("\nEl paquete esta correcto\n");
		pe = 3 + rand () % (11-3);	
		dim = 2 + rand () % (7-2);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
		costo = 50 + rand () % (301-50);			

		notab(pe,dim,costo);
		//desbloqueo a el empleado2
		break;
		
		case 1:
		printf("\nEl paquete esta mal empaquetado\n");
		Empaquetarb();
	
		abrirp=open(pipe_mostrap1,O_RDONLY);
		read(abrirp,mensaje_peso1,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad1,O_RDONLY);
		read(abrird,mensaje_dim1,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac1,O_RDONLY);
		strcpy(mensaje_costo1,"El costo es:"+costo);
		read(abrirc,mensaje_costo1,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap2,O_RDONLY);
		read(abrirp,mensaje_peso2,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad2,O_RDONLY);
		read(abrird,mensaje_dim2,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac2,O_RDONLY);
		read(abrirc,mensaje_costo2,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap3,O_RDONLY);
		read(abrirp,mensaje_peso3,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad3,O_RDONLY);
		read(abrird,mensaje_dim3,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac3,O_RDONLY);
		read(abrirc,mensaje_costo3,MAX);
		close(abrirc);
		exit(0);
		break;
		}

	sleep(2);
	pthread_mutex_unlock(&mutex_mostra2);
	pthread_exit(0);
	}
	



	if(m[3]==getpid())
	{
    pthread_mutex_lock(&mutex_mostra3); 
	printf("\nEsta con el empleado numero %i con identificador %i que verificara si el paquete esta corecto \n",i,getpid());
	srand(time(NULL));
	int random= rand() % 3;
	printf("\nrandom:%i",random);
		switch(random)
		{
		case 0:
		printf("\nEl paquete esta correcto");
		pe = 3 + rand () % (11-3);	
		dim = 2 + rand () % (7-2);
		costo = 50 + rand () % (301-50);
		notab(pe,dim,costo);
			printf("Los datos son:\n");
			printf("\nPeso:%i",pe);
			printf("\ndimension:%i",dim);
			printf("\ncosto:%i",costo);
		//desbloqueo a el empleado3
		break;
		
		case 1:
		printf("\nEl paquete esta mal empaquetado");
		Empaquetarb();

		abrirp=open(pipe_mostrap1,O_RDONLY);
		read(abrirp,mensaje_peso1,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad1,O_RDONLY);
		read(abrird,mensaje_dim1,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac1,O_RDONLY);
		read(abrirc,mensaje_costo1,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap2,O_RDONLY);
		read(abrirp,mensaje_peso2,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad2,O_RDONLY);
		read(abrird,mensaje_dim2,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac2,O_RDONLY);
		read(abrirc,mensaje_costo2,MAX);
		close(abrirc);
		exit(0);

		abrirp=open(pipe_mostrap3,O_RDONLY);
		read(abrirp,mensaje_peso3,MAX);		
		close(abrirp);
		exit(0);

		abrird=open(pipe_mostrad3,O_RDONLY);
		read(abrird,mensaje_dim3,MAX);
		close(abrird);
		exit(0);

		abrirc=open(pipe_mostrac3,O_RDONLY);
		read(abrirc,mensaje_costo3,MAX);
		close(abrirc);
		exit(0);
		break;
		}

	sleep(2);
	pthread_mutex_unlock(&mutex_mostra3);
	pthread_exit(0);
	}
	
}	
wait(&pid);


}







