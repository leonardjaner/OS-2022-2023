/*
 * Filename: pipe2.c
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
	int pipefd[2],n;
	char buffer[100];
	int pid;

	if (pipe(pipefd) < 0)
		err_sys("error with pipe");
	printf("read fd = %d, write fd = %d\n", pipefd[0], pipefd[1]);
	pid=fork();
	if (pid==0) {
		//child process
		if (write(pipefd[1],"hello world\n", 12)!=12) err_sys("write_error");
	}
	else {
	//parent process}
		if ( (n=read(pipefd[0], buffer, sizeof(buffer))) <= 0) err_sys("read_error");
		write(1, buffer, n);
	}
exit(0);
}

