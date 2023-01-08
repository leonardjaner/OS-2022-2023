/*
 * Filename: shm_1a.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include <sys/ioctl.h>
#include <termio.h>

#include <sys/shm.h>
#define SHM_KEY 0x1234

#define STDINFD  0

void err_sys(const char* text)
{
	perror(text);
	exit(1);
} 

struct shmseg {
	int number;
	int process;
	char memory[100];
};


int main(int argc, char *argv[])
{
	int 	input;
	char 	buffer[10+2];
	sem_t*	psem1;	
	sem_t*	psem2;		
	int 	sem_value;
	char 	key;
	int count;
	int shmid;
	struct shmseg *shmp;
	
	if (argc != 3) {
	fprintf(stderr, "USAGE: %s value_sem1 value_sem2\n", argv[0]);
    exit(1);
	}	
	
    shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0666|IPC_CREAT);
	if (shmid == -1) err_sys("Shared Memory Error");

	//attach to the shmp pointer
	shmp = shmat(shmid, NULL, 0);
	if (shmp == (void*)(-1)) err_sys("Shared Memory attachment error");

	shmp->number=1;
	shmp->process = 1;
	strcpy((char*)(shmp->memory),"Sentence");
	
 	if ((psem1 = (sem_t*)sem_open("/semaphore1", O_CREAT, 0600, 0)) == SEM_FAILED) {
    	err_sys("OPEN psem1");
  	}
  	if ((sem_getvalue(psem1, &sem_value)) <0) err_sys("reading sem psem1");
  	printf("PROCESS 1(SEM1): %d\n",sem_value);
	while (sem_value>0) sem_wait(psem1), sem_value--;
	count=0;
	while (count < atoi(argv[1])) {
  	//increment the value of semaphore to initialize it to set argument
		count++;
		if (sem_post(psem1)<0) err_sys("SIGNAL psem1");
	}
	if ((sem_getvalue(psem1, &sem_value)) <0) err_sys("reading sem psem1");
   	printf("PROCESS 1(SEM1): %d\n",sem_value);
	
 	if ((psem2 = (sem_t*)sem_open("/semaphore2", O_CREAT, 0600, 0)) == SEM_FAILED) {
    	err_sys("OPEN psem2");
  	}
  	if ((sem_getvalue(psem2, &sem_value)) <0) err_sys("reading sem psem2");
  	printf("PROCESS 1(SEM2): %d\n",sem_value);
	while (sem_value>0) sem_wait(psem2), sem_value--;
	count=0;
	while (count < atoi(argv[2])) {
		//increment the value of semaphore to initialize it to set argument
		count++;
		if (sem_post(psem2)<0) err_sys("SIGNAL psem2");
	}
	if ((sem_getvalue(psem2, &sem_value)) <0) err_sys("reading sem psem2");
   	printf("PROCESS 1(SEM2): %d\n",sem_value);

	//we can close de semaphore ID
	if (sem_close(psem1)!=0) err_sys("CLOSE psem1");
	if (sem_close(psem2)!=0) err_sys("CLOSE psem2");
}

