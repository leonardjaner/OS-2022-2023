/*
 * Filename: client1.c
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 255

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
  struct sockaddr_in echoserver;
  char buffer[BUFFSIZE];
  unsigned int echolen;
  int sock, result;
  int received = 0;

  /* Check input arguments */
  if (argc != 4) {
    fprintf(stderr, "Usage: client <ip_server> <word> <port>\n");
    exit(1);
  }

  /* Create TCP socket */
  sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0) {
    err_sys("Error socket");
  }

  /* Set information for sockaddr_in */
  memset(&echoserver, 0, sizeof(echoserver));       /* Reset memory */
  echoserver.sin_family = AF_INET;                  /* Internet/IP */
  echoserver.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
  echoserver.sin_port = htons(atoi(argv[3]));       /* Server port */
  
  /* Connect to the server */
  result = connect(sock, (struct sockaddr *) &echoserver, sizeof(echoserver));
  if (result < 0) {
    err_sys("Error connect");
  }

  /* Write to socket */
  write(sock, argv[2], strlen(argv[2]) + 1);
  fprintf(stdout, " sent \n");

  /* Read from socket */
  read(sock, buffer, BUFFSIZE);
  fprintf(stdout, " %s ...done \n", buffer);

  /* Close socket */
  close(sock);

  /* Exit */
  exit(0);
}
