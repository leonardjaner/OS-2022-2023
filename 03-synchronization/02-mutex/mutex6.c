/*
 * Filename: mutex6.c
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

#include <sys/ioctl.h>
#include <termio.h>

#include <pthread.h>

#define STDINFD  0

pthread_mutex_t mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var1  = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_var2  = PTHREAD_COND_INITIALIZER;

int value;
int current_thread = 2;

void err_sys(const char* text)
{
	perror(text);
	exit(1);
}

void *handle_thread1(void *vargp)
{
	int *myiterations = (int *)vargp;
	int count;

	/* Print thread information */
	printf("Executing handle_thread for %d iterations \n", *myiterations);
	fprintf(stdout, "Thread ID in handler %lu\n", pthread_self());

	/* Repeat */
	for (count = 0; count < (*myiterations); count++) {
		/* Aquire mutex */
		pthread_mutex_lock(&mutex);

		/* Check current_thread */
		if (current_thread == 2) {
			/* Wait for cond_var1 */
			pthread_cond_wait(&cond_var1, &mutex);
		}

		/* In critical zone */
		fprintf(stdout, "critical zone, thread %lu %d---%d\n", pthread_self(), count, value++);
		
		/* Update current_thread */
		current_thread = 2;

		/* Signal cond_var2 */
		pthread_cond_signal(&cond_var2);
		
		/* Release mutex */
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void *handle_thread2(void *vargp)
{
	int *myiterations = (int *)vargp;
	int count;

	/* Print thread information */
	printf("Executing handle_thread for %d iterations \n", *myiterations);
	fprintf(stdout, "Thread ID in handler %lu\n", pthread_self());

	/* Repeat */
	for (count = 0; count < (*myiterations); count++) {
		/* Aquire mutex */
		pthread_mutex_lock(&mutex);

		/* Check current_thread */
		if (current_thread == 1) {
			/* Wait for cond_var2 */
			pthread_cond_wait(&cond_var2, &mutex);
		}

		/* In critical zone */
		fprintf(stdout, "critical zone, thread %lu %d---%d\n", pthread_self(), count, value++);
		
		/* Update current_thread */
		current_thread = 1;
		
		/* Signal cond_var1 */
		pthread_cond_signal(&cond_var1);
		
		/* Release mutex */
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}


int main(int argc, char *argv[])
{
	int 	input;
	char 	buffer[10 + 2];
	char 	key;
	int 	iterations;
	int 	errno = 0;
	int 	count;
	int 	result;

	pthread_t handle_thread_id1;
	pthread_t handle_thread_id2;

	/* Parse program arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
		exit(1);
	}

	iterations = atoi(argv[1]);
	value = 0;

	pthread_create(&handle_thread_id1, NULL, handle_thread1, (void *)&iterations);
	fprintf(stdout, "Thread ID for handler %lu\n", handle_thread_id1);

	pthread_create(&handle_thread_id2, NULL, handle_thread2, (void *)&iterations);
	fprintf(stdout, "Thread ID for handler %lu\n", handle_thread_id2);

	/* Wait for thread1 */
	if (pthread_join(handle_thread_id1, NULL)) {
		fprintf(stderr, "Joining thread handle_thread error: errno = %d\n", errno);
		exit(1);
	}

	/* Wait for thread2 */
	if (pthread_join(handle_thread_id2, NULL)) {
		fprintf(stderr, "Joining thread handle_thread error: errno = %d\n", errno);
		exit(1);
	}

	exit(0);
}

