/*
 * Filename: mknod3a.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FIFO_NAME "/tmp/FIFO_FILE"

void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 

int main()
{
	int number=1,n;
    int inputFile, outputFile;

	char buffer[100];
	int pid;

	if (mknod(FIFO_NAME, S_IFIFO|0666, 0) == (-1)) err_sys("Error: could not create FIFO");
	//open S_IFIFO for writing
	outputFile = open(FIFO_NAME, O_WRONLY /*| O_CREAT | O_TRUNC*/, 0644);
	if (outputFile == (-1)) err_sys("Error: could not open FIFO for Writing");
	n = strlen("hello world\n")+1;
	if (write(outputFile,&n, sizeof(int))!=sizeof(int)) err_sys("write_error");
	if (write(outputFile,"hello world\n", n) !=n) err_sys("write_error");
	number = -2;
	if (write(outputFile,&number, sizeof(int))!=sizeof(int)) err_sys("write_error");
	exit(0);
}

