/*
 * Filename: thread2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 

int num1=0;
int num2=0;
int loops;

void *handleThread1(void *unused) 
{ 
int i;
	fprintf(stdout, "Thread ID in handler1 %lu\n", pthread_self());
	for (i=0;i<loops;i++) {
		sleep(1);
		fprintf(stdout,"handler1-%d: num1 %d, num2 %d\n",i,num1,num2);
	}
	exit(1);
}

void *handleThread2(void *unused) 
{ 
int i;
	fprintf(stdout, "Thread ID in handler2 %lu\n", pthread_self());
	for (i=0;i<loops;i++) {
		sleep(2);
		fprintf(stdout,"handler2-%d: num1 %d, num2 %d\n",i,num1++,num2);
	}
	exit(1);
}

void *handleThread3(void *unused) 
{ 
int i;
	fprintf(stdout, "Thread ID in handler3 %lu\n", pthread_self());
	for (i=0;i<loops;i++) {
		sleep(4);
		fprintf(stdout,"handler3-%d: num1 %d, num2 %d\n",i,num1,num2++);
	}
	exit(1);
}

int main(int argc, char *argv[]) {
	
pthread_t handleThreadId1;
pthread_t handleThreadId2;
pthread_t handleThreadId3;

	if (argc!=2) fprintf(stderr,"USAGE: %s <NUM>\n",argv[0]),exit(1);
	loops=atoi(argv[1]);

	pthread_create(&handleThreadId1, NULL, handleThread1, NULL);
	pthread_create(&handleThreadId2, NULL, handleThread2, NULL);
	pthread_create(&handleThreadId3, NULL, handleThread3, NULL);
	pthread_join(handleThreadId1, NULL);
	fprintf(stdout,"Thread1 finished\n");
	pthread_join(handleThreadId2, NULL);
	fprintf(stdout,"Thread2 finished\n");
	pthread_join(handleThreadId3, NULL);
	fprintf(stdout,"Thread3 finished\n");
}