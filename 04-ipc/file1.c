/*
 * Filename: file1.c
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <unistd.h>

void err_sys(const char* cadena)
{
	perror(cadena);
	exit(1);
} 

int main()
{
	int file_write,file_read,n;
	char buffer[100];

	if ((file_write=open("./destination_file.txt",O_WRONLY|O_CREAT|O_TRUNC,00700)) < 0) err_sys("error with destination file");
	printf("write fd = %d\n", file_write);
	if (write(file_write,"hello world\n", 12)!=12) err_sys("write_error");
	if (close(file_write)!=0) err_sys("error close write");

	if ((file_read=open("./destination_file.txt",O_RDONLY)) < 0) err_sys("error with source (destination) file");
	printf("read fd = %d\n", file_read);
	if ( (n=read(file_read, buffer, sizeof(buffer))) <= 0) err_sys("read_error");
	if (close(file_read)!=0) err_sys("error close read");
	
	write(1, buffer, n);
	exit(0);

}

