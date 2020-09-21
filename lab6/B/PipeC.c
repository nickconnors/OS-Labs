#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int fd[2];
	int a, b, c, d, status;
	char read_fd[11];
	char write_fd[11];
	char *arg[3] = {read_fd, write_fd, 0}; 

	a = pipe(fd);
	sprintf(read_fd, "%d", fd[0]);
	sprintf(write_fd, "%d", fd[1]);

	b = fork();
	if (b == 0) {
		execv("PipeW1", arg);
	}

	c = fork();
	if (c == 0) {
		execv("PipeW2", arg);
	}

	d = fork();
	if (d == 0) {
		execv("PipeR", arg);
	}
	exit(0);
}