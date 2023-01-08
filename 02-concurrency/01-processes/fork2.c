/*
 * Filename: fork2.c
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

  /* Check input arguments */
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <value>\n", argv[0]);
    exit(1);
  }

  /* Convert string to integer */
  top = atoi(argv[1]);

  /* Get and print PID and parent PID */
  pid = (int)getpid();
  ppid = (int)getppid();
  fprintf(stdout, "My PID is %d, my parent PID is %d\n", pid, ppid);

  /* Iterate over all input parameters */
  for (i = 0; i < top; i++) {
    fprintf(stdout, "Value: %d\t", i);
  }
  fprintf(stdout, "\n");

  /* Exit program */
  exit(0);
}
