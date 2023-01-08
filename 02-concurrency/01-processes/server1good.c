/*
 * Filename: server1.c
*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>

#define MAXPENDING 5    /* Maximum number of simultaneous connections */
#define BUFFSIZE 255    /* Size of message to be received */

void err_sys(char *mess) { perror(mess); exit(1); }

void handle_client(int sock) {
  char buffer[BUFFSIZE];
  int received = -1;

  /* Read from socket */
  read(sock, &buffer[0], BUFFSIZE);

  /* Print received message */
  printf("Message from client: %s\n", buffer);

  /* Write to socket */
  write(sock, buffer, strlen(buffer) + 1);

  /* Close socket */
  close(sock);
}

int main(int argc, char *argv[]) {
  struct sockaddr_in echoserver, echoclient;
  int serversock, clientsock;
  int returnedpid, result;

  /* Check input arguments */
  if (argc != 2) {
    err_sys("Usage: server <port>\n");
  }

  /* Create TCP socket */
  serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serversock < 0) {
    err_sys("Error socket");
  }

  /* Set information for sockaddr_in structure */
  memset(&echoserver, 0, sizeof(echoserver));       /* Reset memory */
  echoserver.sin_family = AF_INET;                  /* Internet/IP */
  echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any address */
  echoserver.sin_port = htons(atoi(argv[1]));       /* Server port */

  /* Bind */
  result = bind(serversock, (struct sockaddr *) &echoserver, sizeof(echoserver));
  if (result < 0) {
    err_sys("Error bind");
  }

  /* Listen */
  result = listen(serversock, MAXPENDING);
  if (result < 0) {
    err_sys("Error listen");
  }

  /* Loop */
  while (1) {
    unsigned int clientlen = sizeof(echoclient);
    
    /* Wait for a connection from a client */
    clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen);
    if (clientsock < 0) {
      err_sys("Error accept");
    }

    fprintf(stdout, "Client: %s\n", inet_ntoa(echoclient.sin_addr));
    
    /* Fork */
    returnedpid = fork();

    /* Process child and parent processes */
    if (returnedpid != 0) {
      /* parent process */

      /* Close server socket */
      close (serversock);

      /* Handle client */
      handle_client(clientsock);

      /* Exit */
      exit(0);
    }
    else {
      /* child process */
      /* Close client socket */
      close(clientsock);
    }
  }
}
