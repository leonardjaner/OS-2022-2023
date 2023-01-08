/*
 * Filename: sem_1a.c
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

char inkey(void) {
    char c;
    struct termio param_ant, params;

    ioctl(STDINFD, TCGETA, &param_ant);

    params = param_ant;
    params.c_lflag &= ~(ICANON | ECHO);
    params.c_cc[4] = 1;

    ioctl(STDINFD, TCSETA, &params);

    fflush(stdin); fflush(stderr); fflush(stdout);
    read(STDINFD, &c, 1);

    ioctl(STDINFD, TCSETA, &param_ant);
    return c;
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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <iterations>\n", argv[0]);
        exit(1);
    }

    /* Open psem1 */
    psem1 = (sem_t*) sem_open("/sem1", O_CREAT, 0644, 0);
    if (psem1 == SEM_FAILED) {
        err_sys("Open psem1");
    }

    /* Read and print semaphore value */
    result = sem_getvalue(psem1, &sem_value);
    if (result < 0) {
        err_sys("Read psem1");
    }
    printf("PROCESS 1(SEM1): %d\n", sem_value);

    while (sem_value > 0) {
        sem_wait(psem1);
        sem_value--;
    }
    
    /* Read and print semaphore value */
    result = sem_getvalue(psem1, &sem_value);
    if (result < 0) {
        err_sys("Read psem1");
    }
    printf("PROCESS 1(SEM1): %d\n", sem_value);
    
    /* Increment the value of semaphore to initialize it to 1 */
    result = sem_post(psem1);
    if (result < 0) {
        err_sys("Post psem1");
    }
    
    /* Repeat */
    for (count = 0; count < atoi(argv[1]); count++) {
        /* Entering critical zone */
        result = sem_wait(psem1);
        if (result < 0) {
            err_sys("Wait psem1");
        }
        
        /* Critical zone */
        fprintf(stdout, "Critical zone, process A, %d\n", count);

        /* Wait user type any key to continue */
        inkey();

        /* Exiting critical zone */
        result = sem_post(psem1);
        if (result < 0) {
            err_sys("Post psem1");
        }
    }

    /* Close de semaphore ID */
    result = sem_close(psem1);
    if (result != 0) {
        err_sys("Close psem1");
    }
    
    /* Unlink the semaphore (no one is using neither will be able to use again the semaphore */
    result = sem_unlink("/sem1");
    if (result != 0) {
        err_sys("Unlink /sem1");
    }

    exit(0);
}
