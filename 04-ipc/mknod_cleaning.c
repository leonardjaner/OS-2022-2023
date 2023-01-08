/*
 * Filename: mknod_cleaning.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO_NAME "/tmp/FIFO_FILE"

int main(int argc, char** argv) {
	
	unlink(FIFO_NAME);
   }
