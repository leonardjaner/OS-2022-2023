/*
 * Filename: mutex3.c
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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void err_sys(const char* text)
{
    perror(text);
    exit(1);
}

void *handle_thread(void *vargp)
{
    int *myiterations = (int *)vargp;
    int count;

    /* Print thread information */
    printf("Executing handle_thread for %d iterations \n", *myiterations);
    fprintf(stdout, "Thread ID in handler %lu\n", pthread_self());

    /* Repeat */
    for (count = 0; count < (*myiterations); count++) {
        /* Adquire mutex */
        pthread_mutex_lock(&mutex);

        /* In critical zone */
        fprintf(stdout, "Critical zone, thread %lu %d\n", pthread_self(), count);
        
        /* Release mutex */
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int     input;
    char    buffer[10 + 2];
    char    key;
    int     iterations;
    int     errno = 0;
    int     threads;
    int     count;
    int     result;

    pthread_t handle_thread_id[10];

    /* Parse program arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <threads> <iterations>\n", argv[0]);
        exit(1);
    }

    iterations = atoi(argv[2]);
    threads = atoi(argv[1]);

    /* Create and print thread */
    for (count = 0; count < threads; count ++) {
        pthread_create(&handle_thread_id[count], NULL, handle_thread, (void *)&iterations);
        fprintf(stdout, "Thread ID for handler %lu\n", handle_thread_id[count]);
    }

    for (count = 0; count < threads; count ++) {
        result = pthread_join(handle_thread_id[count], NULL);
        if (result > 0) {
            fprintf(stderr, "Joining thread handle_thread error: errno = %d\n", errno);
            exit(1);
        }
    }

    exit(0);
}
