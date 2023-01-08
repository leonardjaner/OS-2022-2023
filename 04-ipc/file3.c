/*
 * Filename: file3.c
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>



void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 

int main()
{
	int file_write,file_read,n;
	int input;
	char buffer[100];

	if ((file_write=open("./destination_file.txt",O_WRONLY|O_CREAT|O_TRUNC,0700)) < 0) err_sys("error with destination file");
	if ((file_read=open("./destination_file.txt",O_RDONLY)) < 0) err_sys("error with source (destination) file");
	if ((input=open("./source_file.txt",O_RDONLY)) < 0) err_sys("error with source_file");

	printf("write fd = %d\n", file_write);
	printf("read fd = %d\n", file_read);
	printf("input fd = %d\n", input);

	if ( (n=read(input, buffer, sizeof(buffer))) <= 0) err_sys("read_error input");
	if (write(file_write,buffer, n)!=n) err_sys("write_error");
	if ( (n=read(file_read, buffer, sizeof(buffer))) <= 0) err_sys("read_error");
	write(1, buffer, n);

	if (close(file_write)!=0) err_sys("error close write");
	if (close(file_read)!=0) err_sys("error close read");
	if (close(input)!=0) err_sys("error close input");
	
	exit(0);

}

