/*
 * Filename: sem_cleaning.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>

#define BUFFER_SIZE 255

void err_sys(const char* text)
{
    perror(text);
    exit(1);
}

int main(int argc, char* argv[])
{
    char buffer[BUFFER_SIZE];
    char* pattern;
    int count, i;
    int result;

    /* Check input arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pattern> <count>\n", argv[0]);
        exit(1);
    }

    pattern = argv[1];
    count  = atoi(argv[2]);

    /* Repeat for all semaphores */
    for (i = 1; i <= count; i++) {
        /* Fill the buffer */
        sprintf(buffer, "/%s_%i", pattern, i);
        puts(buffer);

        /* Unlink the semaphore */
        result = sem_unlink(buffer);
        if (result != 0) {
            sprintf(buffer, "Unlink /%s_%i", pattern, i);
            err_sys(buffer);
        }
    }

    exit(0);
}
