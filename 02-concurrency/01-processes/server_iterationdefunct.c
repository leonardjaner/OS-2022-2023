/*
 * Filename: server_iterationdefunct.c
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXPENDING  2   /* Maximum number of pending connections on server */
#define BUFFSIZE   20   /* Maximum number of bytes per message */

void err_sys(char *mess) { perror(mess); exit(1); }

void handle_client(int sock) {
  char  buffer[BUFFSIZE];
  int   received = -1;
  int   contador;

  for (contador = 0; contador < 3; contador++) {
    /* new message from client */
    buffer[0] = '\0';
    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
      err_sys("error on reading message");
    }
    buffer[received] = '\0';
    /* send back echo */
//  while (received > 0) {
    /* send back echo */
    if (send(sock, buffer, received, 0) != received) {
      err_sys("error writign echo message");
    }
    /* quedan datos por recibir */
//    if ((received = recv(sock, buffer, BUFFSIZE, 0)) < 0) {
//      err_sys("error lectura addicional");
//    }
//  }
    printf("(%d) text : %s", contador, buffer);
  }
  close(sock);
}

int main(int argc, char *argv[]) {
  struct sockaddr_in echoserver, echoclient;
  int serversock, clientsock;
  int returnedpid, result;
  int pid, ppid;

  /* Check input parameters */
  if (argc != 2) {
    err_sys("Usage: server <port>\n");
  }

  /* Create TCP socket*/
  serversock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serversock < 0) {
    err_sys("Error socket");
  }

  /* Set sockaddr_in */
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
    /* New connection request from client? */
    fprintf(stdout, "PARENT PROCESS: Waiting for ACCEPT\n");
    /* Wait for a connection from a client */
    clientsock = accept(serversock, (struct sockaddr *) &echoclient, &clientlen);
    if (clientsock < 0) {
      err_sys("Error accept");
    }
    /* Fork */
    returnedpid = fork();
    /* Process child and parent processes */
    if (returnedpid < 0) {
      err_sys("Error fork");
    }
    else if (returnedpid > 0)
    {
      /* Parent process *//* Close client socket */
      close(clientsock);
      fprintf(stdout, "PARENT PROCESS: I have already forked a new child process\n");
    }
    else
    {
      /* Child process *//* Close server socket */
      close(serversock);
      fprintf(stdout, "Client: %s\n", inet_ntoa(echoclient.sin_addr));
      /* Handle client */
      handle_client(clientsock);
      err_sys("End of child process");
    }
  }
}
