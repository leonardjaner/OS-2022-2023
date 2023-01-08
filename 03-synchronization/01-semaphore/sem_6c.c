/*
 * Filename: sem_6c.c
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
    int count;

    if (argc != 3) {
        fprintf(stderr, "USAGE: %s <iterations> <ID>\n", argv[0]);
        exit(1);
    }
    if ((psem1 = (sem_t*)sem_open("/semaphore1", O_CREAT, 0600, 0)) == SEM_FAILED) {
        err_sys("OPEN psem1");
    }
    if ((psem2 = (sem_t*)sem_open("/semaphore2", O_CREAT, 0600, 0)) == SEM_FAILED) {
        err_sys("OPEN psem2");
    }

    for (count = 0; count < atoi(argv[1]); count++) {
        if (sem_wait(psem2) < 0) err_sys("WAIT psem2");
        //just in the critical zone
        fprintf(stdout, "critical zone, process %s, %d\n", argv[2], count);
        //exiting critical zone
        if (sem_post(psem1) < 0) err_sys("SIGNAL psem1");
    }
    //we can close de semaphore ID
    if (sem_close(psem1) != 0) err_sys("CLOSE psem1");
    if (sem_close(psem2) != 0) err_sys("CLOSE psem2");
}

