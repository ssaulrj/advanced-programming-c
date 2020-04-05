/*Descripci�n programa que permite la comunicaci�n entre dos clientes 
  utilizando  Select


*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>

//Servidor chat, traves de el permite que dos aplicaciones cliente se comuniquen

#define PUERTO 		5000	//numero de puerto asignado servidor
#define COLA_CLIENTES 	5	//tamano de cola para clientes
#define TAM_BUFFER    	100
#define maximo(a,b)	((a) > (b) ? (a) : (b)) //Macro que determina cual de los dos valores es el mayor
#define DIR_IP "127.0.0.1" //Direccion del nodo que contiene la aplicacion servidor

 /*La funcionalidad que contiene la aplicacion cliente, consiste en la
multiplexacion entre el descriptor de archivo que representa al teclado y
el descriptor asociado con el socket
*/
void main(int argc, char **argv){
	int tamano_direccion, sockfd, id_cliente;
	struct sockaddr_in direccion_servidor;
	char mensaje[TAM_BUFFER];
	fd_set conjunto_leer;
	int maximo_fd, n;

	//Se configura la direccion IPv4 para establecer el socket
	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);
	if ( inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0){
		perror("Ocurrio un error al momento de asignar la direccion IP\n");
		exit(1);
	}

	//Limpia el conjunto de lectura
	FD_ZERO(&conjunto_leer);
	printf("Creando Socket ....\n");
	if ( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Ocurrio un problema en la creacion del socket\n");
		exit(1);
	}
	//Creación de las estructuras necesarias para el manejo de un socket
	printf ("Estableciendo conexion ...\n");
	if ( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) {
		perror ("Ocurrio un problema al establecer la conexion\n");
		exit(1);
	}
	printf ("Conectandose al servidor ...\n");
	while (1){
		//Se agregan al conjunto de lectura, tanto el descriptor
		//correspondiente al teclado, como aquel asociado al socket
		FD_SET(fileno(stdin), &conjunto_leer);
		FD_SET(sockfd, &conjunto_leer);
		maximo_fd = maximo(fileno(stdin), sockfd) + 1;
		
        //Se activa la espera indefinia por la ocurrencia de
		//eventos referentes solamente al proceso de lectura
		
		if ( select (maximo_fd, &conjunto_leer, NULL, NULL, NULL) < 0){
			perror ("Ocurrio un problema dentro de la funcion select\n");
			close (sockfd);
		}
		//En este punto de la ejecucion, se sabe que ocurrio un evento
		//con respecto al proceso de lectura, pero no se sabe en cual de
		//los descriptores se disparo el evento
		//Por lo que se procede a cuestionar de manera individual a los
		//descriptores
		//En el caso de que el descriptor haya sido el asociado al
		//socket quien genera el evento, entonces imprime en la terminal
		//el contenido del mensaje
		
		if ( FD_ISSET(sockfd, &conjunto_leer)){
			if (read (sockfd, &mensaje, TAM_BUFFER) < 0){
				perror ("Ocurrio algun problema al recibir datos del cliente\n");
				exit(1);
			}

			printf ("===> %s \n", mensaje);
		}
		//En el caso de que el descriptor haya sido el que representa al
		//teclado quien generó el evento, entonces lee los datos del
		//teclado, y los envía a través del socket
		if ( FD_ISSET(fileno(stdin), &conjunto_leer)){
			if (fgets (mensaje, TAM_BUFFER, stdin) < 0){
				perror ("Ocurrio algun problema al recibir datos del cliente\n");
				exit(1);
			}
			if ( write (sockfd, mensaje, strlen(mensaje) + 1) < 0){
				perror("Ocurrio un problema en el envio de un mensaje al cliente\n");
				exit(1);
			}
		}
	}

	printf ("El servidor envio el siguiente mensaje: \n%s\n", mensaje);
	printf ("Cerrando la aplicacion cliente");
	close(sockfd);
}

