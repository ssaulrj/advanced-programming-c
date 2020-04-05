//Servidor B

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PUERTO 5000
#define COLA_CLIENTES 5 
#define TAM_BUFFER 100

//Numero de  puerto asignado al servidor, tamano de cola espera para clientes 

void main(int argc, char **argv)
{      
	int tamano_direccion, sockfd, cliente_sockfd;
	struct sockaddr_in direccion_servidor; //Estructura que almacena direccion
	char leer_mensaje[TAM_BUFFER];


	//Se configura la direccion IPv4 ppara configurar el socket
	memset(&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);
	direccion_servidor.sin_addr.s_addr = INADDR_ANY;

	//Creacion de las estructuras necesarias para el manejo de sockets
	printf("Creando Socket... \n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0) ) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket\n");
		exit(1);
	}

	//Configuracion del socket mediante la direccion IPv4
	printf("Configurando socket... \n");
	if( bind(sockfd, (struct sockaddr *) &direccion_servidor, sizeof(direccion_servidor) ) < 0 )
	{
		perror("Ocurrio un problema al configurar el socket\n");
		exit(1);
	}
	
	//Define el socket listo para aceptar peticiones
	printf("Estableciendo la aceptacion del cliente... \n");
	if( listen(sockfd, COLA_CLIENTES) < 0 ) 
	{
		perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes\n");
		exit(1);
	}
	
	//Selecciona un cliente de la cola de conexiones establecidas
	//Se crea un nuevo descriptor de socket para el manejo de la nueva  conexion.
	//Apartir de este punto se debe utiliar el nuevo descriptor de socket 
	printf("En espera de peticiones de conexion... \n");
	if( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0)
	{
		perror("Ocurrio algun problema al atender a un cliente\n");
		exit(1);
	}

	//Transferencia de datos entre cliente y servidor 
	printf("Se acepta a un cliente, atendiendolo\n");
	if( read (cliente_sockfd, &leer_mensaje, TAM_BUFFER) < 0)
	{
		perror("Ocurrio algun problema al recibir datos del cliente \n");
		exit(1);
	}

	printf("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
	if( write (cliente_sockfd, "Bienvenido cliente", 19) <0 )
	{
		perror("Ocurrio un problema en el envio de un mensaje a cliente");
		exit(1);
	}

	printf("Concluimos la ejecucion de la aplicacion servidor- \n");
	//Cierre de conexiones

	
	close(sockfd);
	close(cliente_sockfd);
}
