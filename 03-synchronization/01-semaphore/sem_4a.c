/*
 * Filename: sem_4a.c
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
    int     sem_value;
    char    key;
    int     count;
    int     result;

    /* Parse program arguments */
    if (argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(1);
    }

    /* Create psem1 */
    psem1 = (sem_t*)sem_open("/sem_2", O_CREAT, 0600, 0);
    if (psem1 == SEM_FAILED) {
        err_sys("Open psem1");
    }

    /* Read and print psem1 */
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

    /* Increment the value of semaphore to initialize it to 1 */
    result = sem_post(psem1);
    if (result < 0) {
        err_sys("Post psem1");
    }
    
    /* Read and print psem1 */
    result = sem_getvalue(psem1, &sem_value);
    if (result < 0) {
        err_sys("Read psem1");
    }
    printf("PROCESS 1(SEM1): %d\n", sem_value);

    /* Close psem1 */
    result = sem_close(psem1);
    if (result != 0) {
        err_sys("Close psem1");
    }
}
