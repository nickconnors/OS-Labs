#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	/* Part 3, 4, 5, 7: process enters infinite loop */
	printf("Pid %d Code CC: Entering an infinite loop.\n", getpid());
	while (1) {
		usleep(100);
	}	

}
