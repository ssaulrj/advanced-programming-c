#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#define NHijos 2

void hijo1(int fds[2]){

	int numbytes;
	char buf[4096];
	numbytes = read(STDIN_FILENO, buf, sizeof(buf));
	
	while(numbytes > 0){
		if(write(fds[1], buf, strlen(buf)) == -1){
			perror("Fallo en write");
			exit(EXIT_FAILURE);
		}
		if(strncmp("fin\n", buf, strlen("fin\n"))==0)
			break;
		
		numbytes = read(STDIN_FILENO, buf, sizeof(buf));
	}
	if ( numbytes== -1){
			perror("Fallo en read");
			exit(EXIT_FAILURE);	
	}
	close(fds[1]);
}
void hijo2(int fds[2]){

	int numbytes;
	char buf[4096];
	close(fds[1]);
	numbytes = read(fds[0], buf, sizeof(buf));
	
	while(numbytes > 0){
		if(strncmp("fin\n", buf, strlen("fin\n"))==0)
			break;
		if(write(STDOUT_FILENO, buf, strlen(buf)) == -1){
			perror("Fallo en write");
			exit(EXIT_FAILURE);
		}

		numbytes = read(fds[0], buf, sizeof(buf));
	}
	if ( numbytes== -1){
			perror("Fallo en read");
			exit(EXIT_FAILURE);	
	}
	close(fds[0]);
}
int main(void){
	int ret, i, fds[2];
	
	if(pipe(fds)==-1){
		perror("Fallo en pipe");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<NHijos; i++){
		ret = fork();
		if(ret==0){
			switch(i){
				case 0:
				  hijo1(fds);
				  exit(EXIT_SUCCESS);
				case 1:
				  hijo2(fds);
				  exit(EXIT_SUCCESS);
			}
		} else if(ret>0){
		} else if(ret==-1){
			perror("Fallo en fork");
			exit(EXIT_FAILURE);
		}
	}
	
	close(fds[0]);
	close(fds[1]);
	ret=wait(NULL);
	while(ret>0){
		ret=wait(NULL);
	}
	if(ret==-1 && errno !=ECHILD){
		perror("Fallo en wait");
		exit(EXIT_FAILURE);
	}
}
