/*
 * Filename: udp_client1.c
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 5

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
  struct sockaddr_in echoserver, echoclient;
  unsigned int echolen, clientlen;
  char buffer[BUFFSIZE];
  int sock, result;
  int received = 0;

  /* Check input arguments */
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <ip_server> <word> <port>\n", argv[0]);
    exit(1);
  }

  /* Create UDP socket */
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    err_sys("Error on socket creation");
  }

  /* Configure/set socket address for the server */
  memset(&echoserver, 0, sizeof(echoserver));       /* Erase the memory area */
  echoserver.sin_family = AF_INET;                  /* Internet/IP */
  echoserver.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
  echoserver.sin_port = htons(atoi(argv[3]));       /* Server port */

  /* Try to send the word to server */
  echolen = strlen(argv[2]);
  result = sendto(sock, argv[2], echolen, 0, (struct sockaddr *) &echoserver, sizeof(echoserver));
  if (result != echolen) {
    err_sys("error writing word on socket");
  }

  /* Set the maximum size of address to be received */
  clientlen = sizeof(echoclient);

  /* Wait for echo from server */
  fprintf(stdout, "Server echo: ");
  received = recvfrom(sock, buffer, BUFFSIZE, 0, (struct sockaddr *) &echoclient, &clientlen);
  if (received != echolen) {
    err_sys("Error reading");
  }

  /* Terminate received buffer */
  buffer[received] = '\0';

  /* Print word on screen */
  fprintf(stdout, "%s", buffer);
  fprintf(stdout, "\n");

  /* Close socket */
  close(sock);

  exit(0);
}
