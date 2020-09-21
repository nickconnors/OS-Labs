#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	/* Part 13: Print arguments */
	printf("Pid %d Code FF: argument 1: %s\t argument 2: %s\t argument 3: %s. Terminating\n", getpid(), argv[0], argv[1], argv[2]);
}
