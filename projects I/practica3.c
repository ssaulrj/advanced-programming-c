#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char *argv[]){
if(argc!=2){
    printf("Numero de parametros incorrectos. USo %s [entero] \n",argv[0]);
    exit(EXIT_FAILURE);
}
       int ret;
       int valor=atoi(argv[1]);
       char c;
       int i;
 printf("El tamaño de %s es: %d \n",argv[1],strlen(argv[1]));
        for(i=0;i<strlen(argv[1]);i++){
              c=argv[1][i];
              if(isdigit(c)==0){
                        perror("fallo en insertar el argumento,debe de ser un numero");
                        exit(EXIT_FAILURE);
                               }
                              }
              ret=fork();
              if(ret==-1){
                     perror("Fallo en el fork()");
                     exit(EXIT_FAILURE);
                         }else if(ret>0){
                            valor+=2;
                            printf("El valor del padre es %d\n",valor);
                            wait(NULL);
                            }else if(ret==0){
                               valor-=4;
                               printf("El valor del hijo es %d\n",valor);
                               exit(EXIT_SUCCESS);

                        }
                        }
                           
