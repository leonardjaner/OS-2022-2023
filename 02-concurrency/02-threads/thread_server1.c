/*
 * Filename: threads_server1.c
*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <pthread.h> 



#define MAXPENDING 5    /* maximum number of simultaneous connections */
#define BUFFSIZE 255		// size of message to be reeived
void err_sys(char *mess) { perror(mess); exit(1); }

void *handleThread(void *vargp) 
{ 
int *mysock = (int *)vargp; 
char buffer[BUFFSIZE];
int received = -1;

printf("Executing handleThread with socket descriptor ID: %d\n", *mysock); 
fprintf(stdout, "Thread ID in handler %lu\n", pthread_self());

read(*mysock,&buffer[0],BUFFSIZE);
printf("message from client: %s\n", buffer);
write(*mysock,buffer,strlen(buffer)+1);
close(*mysock);
return((void*)NULL);
}


int main(int argc, char *argv[]) {
int serversock, clientsock;
struct sockaddr_in echoserver, echoclient;

pthread_t handleThreadId;

if (argc != 2) {
	err_sys("USAGE: server <port>\n");
}
/* we create TCP socket */
if ((serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	err_sys("error while trying to create socket");
}
/* we set information for sockaddr_in structure*/
memset(&echoserver, 0, sizeof(echoserver));       /* we reset memory */
echoserver.sin_family = AF_INET;                  /* Internet/IP */
echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* ANY address */
echoserver.sin_port = htons(atoi(argv[1]));       /* server port */
/* Bind  */
if (bind(serversock, (struct sockaddr *) &echoserver,sizeof(echoserver)) < 0) {
	err_sys("error bind");
}
/* Listen  */
if (listen(serversock, MAXPENDING) < 0) {
	err_sys("error listen");
}
/* loop */
while (1) {
	unsigned int clientlen = sizeof(echoclient);
    /* we wait for a connection from a client */
    if ((clientsock =
    	accept(serversock, (struct sockaddr *) &echoclient,&clientlen)) < 0) {
		err_sys("error accept");
	}
    fprintf(stdout, "Client: %s\n",inet_ntoa(echoclient.sin_addr));
    pthread_create(&handleThreadId, NULL, handleThread, (void *)&clientsock);
	fprintf(stdout, "Thread ID for handler %lu\n", handleThreadId);
//    pthread_join(handleThreadId, NULL);

/*
	if (fork()==0) {
		//child process
		close (serversock);
		HandleClient(clientsock);
		exit(0);
	}
	else {
		//parent process
		close(clientsock);
	}
*/
}
}


