/*
 * Filename: sem_7b.c
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
    sem_t*  psem2;
    int     sem_value;
    char    key;
    int     count;
    int     result;

    /* Parse program arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <iterations> <ID>\n", argv[0]);
        exit(1);
    }

    /* Create psem1 */
    psem1 = (sem_t*)sem_open("/semaphore1", O_CREAT, 0600, 0);
    if (psem1 == SEM_FAILED) {
        err_sys("Open psem1");
    }

    /* Create psem2 */
    psem2 = (sem_t*)sem_open("/semaphore2", O_CREAT, 0600, 0);
    if (psem2 == SEM_FAILED) {
        err_sys("Open psem2");
    }

    /* Repeat */
    for (count = 0; count < atoi(argv[1]); count++) {
        /* Entering critical zone */
        result = sem_wait(psem1);
        if (result < 0) {
            err_sys("Wait psem1");
        }

        /* Critical zone */
        fprintf(stdout, "Critical zone, process %s, %d\n", argv[2], count);
        
        /* Exiting critical zone */
        result = sem_post(psem2);
        if (result < 0) {
            err_sys("Signal psem2");
        }
    }

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
