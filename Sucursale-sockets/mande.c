//Conexion a 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PUERTO 7000
#define TAM_BUFFER 100
#define DIR_IP "127.0.0.1"

//numero de puerto asignado al servidor 
//Direccion del servidor

int main()
{
  system("telnet localhost 8008");
  return 0;
}
