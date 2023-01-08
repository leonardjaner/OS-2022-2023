/*
 * Filename: thread1.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 

int num1=0;
int num2=0;

void *handleThread1(void *unused) 
{ 
	fprintf(stdout, "Thread ID in handler1 %lu\n", pthread_self());
	while (1) {
		sleep(1);
		fprintf(stdout,"handler1: num1 %d, num2 %d\n",num1,num2);
	}
}

void *handleThread2(void *unused) 
{ 
	fprintf(stdout, "Thread ID in handler2 %lu\n", pthread_self());
	while (1) {
		sleep(2);
		fprintf(stdout,"handler2: num1 %d, num2 %d\n",num1++,num2);
	}
}

void *handleThread3(void *unused) 
{ 
	fprintf(stdout, "Thread ID in handler3 %lu\n", pthread_self());
	while (1) {
		sleep(4);
		fprintf(stdout,"handler3: num1 %d, num2 %d\n",num1,num2++);
	}
}

int main(int argc, char *argv[]) {
pthread_t handleThreadId1;
pthread_t handleThreadId2;
pthread_t handleThreadId3;

	pthread_create(&handleThreadId1, NULL, handleThread1, NULL);
	pthread_create(&handleThreadId2, NULL, handleThread2, NULL);
	pthread_create(&handleThreadId3, NULL, handleThread3, NULL);
	pthread_join(handleThreadId1, NULL);
	pthread_join(handleThreadId2, NULL);
	pthread_join(handleThreadId3, NULL);
}