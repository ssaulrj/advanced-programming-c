
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

/** Puerto  */
#define PORT  8008

/** Número máximo de hijos */
#define MAX_CHILDS 3

/** Longitud del buffer  */
#define BUFFERSIZE 512
#define NNN 1

int AtiendeCliente(int socket, struct sockaddr_in addr);
int DemasiadosClientes(int socket, struct sockaddr_in addr);
void error(int code, char *err);
void reloj(int loop);

int main(int argv, char** argc){

    int socket_host;
    struct sockaddr_in client_addr;
    struct sockaddr_in my_addr;
    struct timeval tv;     
    socklen_t size_addr = 0;
    int socket_client;
    fd_set rfds;        /* Conjunto de descriptores a vigilar */
    int childcount=0;
    int exitcode;

    int childpid;
    int pidstatus;

    int activated=1;
    int loop=0;
    socket_host = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_host == -1)
      error(1, "No puedo inicializar el socket");
    
    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY ;

    
    if( bind( socket_host, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 )
      error(2, "El puerto está en uso"); /* Error al hacer el bind() */

    if(listen( socket_host, 10) == -1 )
      error(3, "No puedo escuchar en el puerto especificado");

    size_addr = sizeof(struct sockaddr_in);


    while(activated)
      {
    reloj(loop);
    
    FD_ZERO(&rfds);
    FD_SET(socket_host, &rfds);

   
    tv.tv_sec = 0;
    tv.tv_usec = 500000;    /* Tiempo de espera */
    
    if (select(socket_host+1, &rfds, NULL, NULL, &tv))
      {
        if((socket_client = accept( socket_host, (struct sockaddr*)&client_addr, &size_addr))!= -1)
          {
        loop=-1;       
        printf("\nSe ha conectado %s por su puerto %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
        switch ( childpid=fork() )
          {
          case -1: 
            error(4, "No se puede crear el proceso hijo");
            break;
          case 0:   /* Somos proceso hijo */
            if (childcount<MAX_CHILDS)
              exitcode=AtiendeCliente(socket_client, client_addr);
            else
              exitcode=DemasiadosClientes(socket_client, client_addr);

            exit(exitcode); 
          default:  /* Somos proceso padre */
            childcount++; /* Acabamos de tener un hijo */
            close(socket_client); 
            break;
          }
          }
        else
          fprintf(stderr, "ERROR AL ACEPTAR LA CONEXIÓN\n");
      }

    /* Miramos si se ha cerrado algún hijo últimamente */
    childpid=waitpid(0, &pidstatus, WNOHANG);
    if (childpid>0)
      {
        childcount--;   /* Se acaba de morir un hijo */

        if (WIFEXITED(pidstatus))
          {
        if (WEXITSTATUS(pidstatus)==99)
          {
            printf("\nSe ha pedido el cierre del programa\n");
            activated=0;
          }
          }
      }
    loop++;
    }

    close(socket_host);

    return 0;
}


int DemasiadosClientes(int socket, struct sockaddr_in addr)
{
    int buffer;
    int bytecount;
    
    printf("Demasiados clientes conectados. Por favor, espere unos minutos\n");

    //if((bytecount = send(socket, buffer, buffer, 0))== -1)
    //error(6, "No puedo enviar información");
    
    close(socket);

    return 0;
}

int AtiendeCliente(int socket, struct sockaddr_in addr)
{

    char buffer[BUFFERSIZE];
   // int buffer=0;
    char aux[BUFFERSIZE];
    int bytecount;
    int fin=0;
    int code=0;         /* Código de salida por defecto */
    time_t t;
    struct tm *tmp;

 while (!fin)
 {  printf("\n Leer sucursal  de REMITENTE Y DESTINATARIO: - ");
    memset(buffer, 0, BUFFERSIZE);
    
	
    if((bytecount = recv(socket, buffer, BUFFERSIZE, 0))== -1)
      error(5, "No puedo recibir información");

    /* Evaluamos los comandos fin termina conexion*/
    /* Comando A a A*/
    if ( (strncmp(buffer, "AA", 2)==0) )
      {
        memset(buffer, 0, BUFFERSIZE);

       printf("Paquete de A al A\n");
       sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
       fin=1;
      }
    /* Comando B a B*/
    else if (   (strncmp(buffer, "BB", 2)==0)  )
      {
        memset(buffer, 0, BUFFERSIZE);
  
        printf("Paquete de B al B\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
    /* Comando C al C*/
    else if (  (strncmp(buffer, "CC", 2)==0)  )
      {
        memset(buffer, 0, BUFFERSIZE);
    
        printf("Paquete de C al C\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
     /* Comando A al B*/
    else if (   (strncmp(buffer, "AB", 2)==0) )
      {
        memset(buffer, 0, BUFFERSIZE);
    
        printf("Paquete de A al B\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
    /* Comando A al C*/
    else if (  (strncmp(buffer, "AC", 2)==0)   )
      {
        memset(buffer, 0, BUFFERSIZE);

        printf("Paquete de A al C\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
    /* Comando B al A*/
    else if (   (strncmp(buffer, "BA", 2)==0) )
      {
        memset(buffer, 0, BUFFERSIZE);
        
        printf("Paquete de B al A\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
    /* Comando B al C*/
    else if (  (strncmp(buffer, "BC", 2)==0)   )
      {
        memset(buffer, 0, BUFFERSIZE);
       
        printf("Paquete de B al C\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
    /* Comando C al A*/
    else if (   (strncmp(buffer, "CA", 2)==0)  )
      {
        memset(buffer, 0, BUFFERSIZE);
        
        printf("Paquete de C al A\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
    /* Comando C al B*/
    else if (  (strncmp(buffer, "CB", 2)==0)    )
      {
        memset(buffer, 0, BUFFERSIZE);
       
        printf("Paquete de C al B\n");
	sprintf(buffer, "Hasta luego. %s\n", inet_ntoa(addr.sin_addr));
	fin=1;
      }
	
    /* Comando EXIT - Cierra la conexión actual 
    else if (strncmp(buffer, "EXIT", 4)==0)
      {
        memset(buffer, 0, BUFFERSIZE);
        sprintf(buffer, "Hasta luego. Vuelve pronto %s\n", inet_ntoa(addr.sin_addr));
        fin=1;
      }*/
    
    else
      {     
        sprintf(aux, "Mala sucursal: %s\n", buffer);
        strcpy(buffer, aux);
      }

    if((bytecount = send(socket, buffer, strlen(buffer), 0))== -1)
      error(6, "No puedo enviar información");
 }

    close(socket);
    return code;
}

void reloj(int loop)
{
  if (loop==0)
    printf("[SERVIDOR] Esperando conexión  ");

  printf("\033[1D");      
  switch (loop%4)
    {
    case 0: printf("."); break;
    case 1: printf("-"); break;
    case 2: printf("./"); break;
    case 3: printf("-"); break;
    default:           
      break;
    }
  fflush(stdout);      
}

void error(int code, char *err)
{
  char *msg=(char*)malloc(strlen(err)+14);
  sprintf(msg, "Error %d: %s\n", code, err);
  fprintf(stderr, msg);
  exit(1);
}        
