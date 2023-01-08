/*
 * Filename: fork4.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void err_sys(char *mess) { perror(mess); exit(1); }

int main(int argc, char *argv[]) {
  int pid, ppid;
  int i, top;
  int returnedpid;

  /* Check input arguments */
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <value>\n", argv[0]);
    exit(1);
  }

  /* Create a new process */
  returnedpid = fork();

  /* Get and print PID and parent PID */
  pid = (int)getpid();
  ppid = (int)getppid();
  fprintf(stdout, "fork() returned %d. My PID is %d, my parent PID is %d\n", returnedpid, pid, ppid);

  /* Wait forever */
  while (1);

  exit(0);
}
