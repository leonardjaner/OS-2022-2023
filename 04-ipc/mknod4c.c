/*
 * Filename: mknod4c.c
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

	inputFile = open(FIFO_NAME, O_RDONLY);
	if (inputFile == (-1)) err_sys("Error: could not open FIFO for Reading");
	if ( (n=read(inputFile, &number, sizeof(int))) <= 0) err_sys("read_error");
	fprintf(stdout,"now the number is %d\n", number);
	exit(0);
}

