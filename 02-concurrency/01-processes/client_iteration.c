/*
 * Filename: client_iteration.c
 */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 20

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
  struct sockaddr_in echoserver;
  char buffer[BUFFSIZE];
  unsigned int echolen;
  int sock, result;
  int received = 0;
  int counter;
  int bytes = 0;

  /* */
  if (argc != 3) {
    fprintf(stderr, "USAGE: %s <ip_server> <port>\n", argv[0]);
    exit(1);
  }

  /* Create TCP socket */
  sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0) {
    err_sys("errpr socket");
  }

  /* set sockaddr_in */
  memset(&echoserver, 0, sizeof(echoserver));       /* Reset memory */
  echoserver.sin_family = AF_INET;                  /* Internet/IP */
  echoserver.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
  echoserver.sin_port = htons(atoi(argv[2]));       /* Server port */

  /* Connect to server */
  result = connect(sock, (struct sockaddr *) &echoserver, sizeof(echoserver));
  if (result < 0) {
    err_sys("Error connect");
  }

  /* Send word to server */
  for (counter = 0; counter < 3; counter++) {
    buffer[0] = '\0';
    printf("(%d) which word?\n", counter);
    fgets(buffer, BUFFSIZE - 1, stdin);
    echolen = strlen(buffer);
    
    result = send(sock, buffer, echolen, 0);
    if (result != echolen) {
      err_sys("error writing");
    }

    /* Echo */
    fprintf(stdout, "ECHO: ");
    
    buffer[0] = '\0';
//while (received < echolen) {
    bytes = 0;
    if ((bytes = recv(sock, buffer, BUFFSIZE - 1, 0)) < 1) {
      err_sys("error reading");
    }
    buffer[bytes] = '\0';        /* \0 */
    fprintf(stdout, "%s", buffer);
//}
    fprintf(stdout, "\n");

  }

  close(sock);
  exit(0);
}
