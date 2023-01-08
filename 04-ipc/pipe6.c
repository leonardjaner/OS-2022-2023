/*
 * Filename: pipe6.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 

int main()
{
	int pipefd[2],number=1,n;
	char buffer[100];
	int pid;
	
    time_t timer;
    struct tm* tm_info;

	if (pipe(pipefd) < 0) err_sys("error with pipe");
	printf("read fd = %d, write fd = %d\n", pipefd[0], pipefd[1]);
	pid=fork();
	if (pid==0) {
		//child process
		n = strlen("hello world\n")+1;
		if (write(pipefd[1],&n, sizeof(int))!=sizeof(int)) err_sys("write_error");
		if (write(pipefd[1],"hello world\n", n) !=n) err_sys("write_error");
		number = -2;
		sleep(5);
		if (write(pipefd[1],&number, sizeof(int))!=sizeof(int)) err_sys("write_error");
	}
	else {
	//parent process}
		fprintf(stdout,"the number is %d\n", number);
		if ( (n=read(pipefd[0], &number, sizeof(int))) <= 0) err_sys("read_error");
		if ( (n=read(pipefd[0], buffer, number)) != number) err_sys("read_error");
		write(1, buffer, n);
		fprintf(stdout,"the number of characters on text are %d\n",n);


		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
		puts(buffer);

		if ( (n=read(pipefd[0], &number, sizeof(int))) <= 0) err_sys("read_error");

		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
		puts(buffer);

		fprintf(stdout,"now the number is %d\n", number);

	}
exit(0);
}

