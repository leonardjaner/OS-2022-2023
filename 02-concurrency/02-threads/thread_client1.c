/*
 * Filename: threads_client1.c
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
int sock;
struct sockaddr_in echoserver;
char buffer[BUFFSIZE];
unsigned int echolen;
int received = 0;

if (argc != 4) {
	fprintf(stderr, "USAGE: client <ip_server> <word> <port>\n");
    exit(1);
}
/* we try to create TCP socket */
if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	err_sys("error socket");
}
/* we set information for sockaddr_in */
memset(&echoserver, 0, sizeof(echoserver));       /* reset memory */
echoserver.sin_family = AF_INET;                  /* Internet/IP */
echoserver.sin_addr.s_addr = inet_addr(argv[1]);  /* IP address */
echoserver.sin_port = htons(atoi(argv[3]));       /* server port */
/* we try to have a connection with the server */
if (connect(sock,(struct sockaddr *) &echoserver,sizeof(echoserver)) < 0) {
              err_sys("error connect");
}
write(sock,argv[2],strlen(argv[2])+1);
fprintf(stdout, " sent \n");
read(sock,buffer, BUFFSIZE);
fprintf(stdout, " %s ...done \n",buffer);
close(sock);
exit(0);
}