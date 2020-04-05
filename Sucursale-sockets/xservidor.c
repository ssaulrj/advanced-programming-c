/*Descripcion programa que permite la comunicacion entre dos clientes
  utilizando  Select y un servidor con el pool de conexiones


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>

void* funcion_accept(void * argumento);
int funcion_maximo();
//Servidor chat, traves de el permite que dos aplicaciones cliente se comuniquen

#define PUERTO 		5000	//numero de puerto asignado servidor
#define COLA_CLIENTES 	5	//tamano de cola para clientes
#define TAM_BUFFER    	100
#define TAM_CADENA      35   //Se define el tamaño de la cadena que lleva el nombre de los clientes
            //Macro que determina cual de los dos valores es el mayor
#define maximo(a,b)   	((a) > (b) ? (a) : (b))


typedef struct {
    char nombre_cliente[TAM_CADENA];
    //struct sockaddr_in	direccion_servidor;
} mystruct; //32#

int xxx;
int cliente_sockfd1, cliente_sockfd2;
int sockfd[COLA_CLIENTES], cliente_sockfd[COLA_CLIENTES];
int contador=0;
mystruct Clientes[COLA_CLIENTES];
pthread_t id_hilo[COLA_CLIENTES];

void main(int argc, char **argv)
{
	int 	tamano_direccion;
	struct 	sockaddr_in	direccion_servidor;
	fd_set	conjunto_leer;
	int		maximo_fd;
	char	mensaje[TAM_BUFFER];

	//Se configura la direccion IPv4 para establecer el socket

	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);
	direccion_servidor.sin_addr.s_addr = INADDR_ANY;

	FD_ZERO(&conjunto_leer); 	//Limpia el conjunto de lectura

	//Creacion de las estructuras necesarias para el manejo de un socket
	printf("Creando Socket ....\n");

	if ( (sockfd[contador] = socket (AF_INET, SOCK_STREAM, 0)) < 0)
        {
		perror("Ocurrio un problema en la creacion del socket\n");
		exit(1);
	}//if

	printf("Configurando socket ...\n");
	if (bind(sockfd[contador], (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor)) < 0)
   {
		    perror ("Ocurrio un problema al configurar el socket\n");
		    exit(1);
	}//if

	printf ("Estableciendo la aceptacion de clientes...\n");
	if ( listen(sockfd[contador], COLA_CLIENTES) < 0)
   {
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit(1);
	}//if

	//Se aceptan solamente hilos clientes dependiendo del tamaño de COLA DE CLIENTES

     for(int i=0; i<COLA_CLIENTES;i++)
        {
         /*crea el hilo para mandar llamar a la funcion que aceptar� a cada uno de los clientes*/
	      if ( pthread_create(&id_hilo[contador], NULL, funcion_accept, NULL))
           {
	         	perror("Problema en la creación del hilodel accept\n");
		         exit(EXIT_FAILURE);
           }
        }


	//Se integran los dos descriptores de socket al conjunto en el
	//cual estamos interesados en poder realizar lecturas

	//Se determina cual de los dos descriptores es el mayor y descriptor
	//ganador se se suma el valor de 1


    while (1)
    {
       FD_SET(cliente_sockfd[contador], &conjunto_leer);

        maximo_fd = funcion_maximo()+1;

		//Se activa la espera indefinia por la ocurrencia de eventos
		//solamente al proceso de lectura
		if ( select (maximo_fd, &conjunto_leer, NULL, NULL, NULL) < 0){
			perror ("Ocurrio un problema dentro de la funcion select\n");

         for(int i=0; i<5;i++){
         	close (cliente_sockfd[i]);
			   close (sockfd[i]);
         }
		}//if

 		//En este punto de la ejecucion, se sabe que ocurrio un evento con
		//respecto al proceso de lectura, pero no se sabe en cual de los
		//descriptores se disparó el evento
		//Por lo que se procede a cuestionar de manera individual a los descriptores
		//En el caso de que el descriptor cliente_sockfd1 haya sido quien
		//genera siguiente el evento, entonces se procede de acuerdo a lo


		if ( FD_ISSET(cliente_sockfd1, &conjunto_leer))
        {
			//La funcion consiste en simplemente, leer del socket que esta
			//listo, y se reenvian los datos por el otro socket
			if (read (cliente_sockfd1, &mensaje, TAM_BUFFER) < 0)
            {
				perror ("Ocurrio algun problema al recibir datos del cliente\n");
				exit(1);
			}//if

            if (strcmp(mensaje, "SALIR") == 0)
			     exit(1);
            printf ("El cliente 1 nos envio el siguiente mensaje: \n %s %d y lo reenviamos al cliente 2\n", mensaje, strlen(mensaje));
		    if (write (cliente_sockfd2, mensaje, strlen(mensaje)+1) < 0)
            {
			  perror("Ocurrio un problema en el envio de un mensaje al cliente\n");
			  exit(1);
		     }//if
        }//if

	    //En el caso de que el descriptor cliente_sockfd2 haya sido quien
	    //genera el evento, entonces procede de acuerdo a lo siguiente
	    if ( FD_ISSET(cliente_sockfd2, &conjunto_leer))
        {
		   if (read (cliente_sockfd2, &mensaje, TAM_BUFFER) < 0)
           {
		   	  perror ("Ocurrio algun problema al recibir datos del cliente\n");
			  exit(1);
		   }//if
		   if (strcmp(mensaje, "SALIR") == 0)
				exit(1);
		   //La funcion consiste en simplemente, leer del socket que esta
		   //listo, y se reenvian los datos por el otro socket
		   printf ("El cliente 2 nos envio el siguiente mensaje: \n %s %d y lo reenviamos al cliente 1\n", mensaje, strlen(mensaje));
		   if (write (cliente_sockfd1, mensaje, strlen(mensaje)+1) < 0)
           {
		      perror("Ocurrio un problema en el envio de un mensaje al cliente\n");
		      exit(1);
		   }//if
	   }//if
    }//while
  close (*sockfd);
}//main

void* funcion_accept(void * argumento)
{
  
   printf ("Entro a la funcion accept ...\n");
   printf ("En espera de ingreso cliente  ...\n");

	if ((cliente_sockfd[contador] = accept(sockfd[contador], NULL, NULL)) < 0){
		perror("Ocurrio un problema al atender a un cliente\n");
		
		exit(1);
	}//if
   contador=contador+1;
   sleep(3);
   pthread_exit("finalizando el hilo de la funcion accept\n");
}


int funcion_maximo()
{
  int cont =0;
  int max=cliente_sockfd[0];
  for(int i=1;i<5;i++)
         if (cliente_sockfd[i]>= max)
             max=cliente_sockfd[i];
  return max;
}
