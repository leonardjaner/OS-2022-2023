/*
 * Filename: shm_1cleaming.c
 */

#include <stdio.h>
#include <stdlib.h>

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


void main()
{

	if (sem_unlink("/semaphore1")!=0) err_sys("UNLINK /semaphore1");
	if (sem_unlink("/semaphore2")!=0) err_sys("UNLINK /semaphore2");
	exit(0);

}

