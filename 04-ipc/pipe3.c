/*
 * Filename: pipe3.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 

int main()
{
	int pipefd[2],n=1;
	char buffer[100];
	int pid;

	if (pipe(pipefd) < 0) err_sys("error with pipe");
	printf("read fd = %d, write fd = %d\n", pipefd[0], pipefd[1]);
	pid=fork();
	if (pid==0) {
		//child process
		if (write(pipefd[1],"hello world\n", 12)!=12) err_sys("write_error");
		n = 2;
		if (write(pipefd[1],&n, sizeof(int))!=sizeof(int)) err_sys("write_error");
	}
	else {
	//parent process}
		fprintf(stdout,"the number is %d\n", n);
		if ( (n=read(pipefd[0], buffer, sizeof(buffer))) <= 0) err_sys("read_error");
		write(1, buffer, n);
		if ( (n=read(pipefd[0], &n, sizeof(int))) <= 0) err_sys("read_error");
		fprintf(stdout,"now the number is %d\n", n);

	}
exit(0);
}

