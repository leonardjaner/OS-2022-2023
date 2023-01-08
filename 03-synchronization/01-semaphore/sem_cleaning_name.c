/*
 * Filename: sem_cleaning_name.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>


void err_sys(const char* text)
{
	perror(text);
	exit(1);
} 


int main(int argc, char* argv[])
{

    /* Check input arguments */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <name>\n", argv[0]);
        exit(1);
    }

	if (sem_unlink(argv[1])!=0) err_sys(strcat("UNLINK ",argv[1]));
	exit(0);
}

