/*
 * Filename: sem_6a.c
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

#define STDINFD  0

void err_sys(const char* text)
{
    perror(text);
    exit(1);
}

int main(int argc, char *argv[])
{
    int     input;
    char    buffer[10 + 2];
    sem_t*  psem1;
    sem_t*  psem2;
    int     sem_value;
    char    key;
    int     count;
    int     result;

    /* Parse program arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s value_sem1 value_sem2\n", argv[0]);
        exit(1);
    }

    /* Create psem1 */
    psem1 = (sem_t*)sem_open("/semaphore1", O_CREAT, 0600, 0);
    if (psem1 == SEM_FAILED) {
        err_sys("Open psem1");
    }

    /* Read and print psem1 value */
    result = sem_getvalue(psem1, &sem_value);
    if (result < 0) {
        err_sys("Read psem1");
    }
    printf("PROCESS 1(SEM1): %d\n", sem_value);
    
    /* Wait for sem_value to be 0 */
    while (sem_value > 0) {
        sem_wait(psem1);
        sem_value--;
    }
    
    /* Repeat */
    count = 0;
    while (count < atoi(argv[1])) {
        /* Increment the value of semaphore to initialize it to set argument */
        count++;

        /* Post to psem1 */
        result = sem_post(psem1);
        if (result < 0) {
            err_sys("Post psem1");
        }
    }
    
    /* Read and print psem1 value */
    result = sem_getvalue(psem1, &sem_value);
    if (result < 0) {
        err_sys("Read psem1");
    }
    printf("PROCESS 1(SEM1): %d\n", sem_value);

    /* Create psem2 */
    psem2 = (sem_t*)sem_open("/semaphore2", O_CREAT, 0600, 0);
    if (psem2 == SEM_FAILED) {
        err_sys("Open psem2");
    }
    
    /* Read and print psem2 value */
    result = sem_getvalue(psem2, &sem_value);
    if (result < 0) {
        err_sys("Read psem2");
    }
    printf("PROCESS 1(SEM2): %d\n", sem_value);
    
    /* Wait for sem_value to be 0 */
    while (sem_value > 0) {
        sem_wait(psem2);
        sem_value--;
    }
    
    /* Repeat */
    count = 0;
    while (count < atoi(argv[2])) {
        /* Increment the value of semaphore to initialize it to set argument */
        count++;

        /* Post to psem1 */
        result = sem_post(psem2);
        if (result < 0) {
            err_sys("Post psem2");
        }
    }

    /* Read and print psem2 value */
    result = sem_getvalue(psem2, &sem_value);
    if (result < 0) {
        err_sys("Read psem2");
    }
    printf("PROCESS 1(SEM2): %d\n", sem_value);

    /* Close psem1 */
    result = sem_close(psem1);
    if (result != 0) {
        err_sys("Close psem1");
    }

    /* Close psem2 */
    result = sem_close(psem2);
    if (result != 0) {
        err_sys("Close psem2");
    }
}
