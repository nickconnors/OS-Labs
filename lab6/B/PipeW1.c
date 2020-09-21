#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int i;
	char bWrite[7];

	close(atoi(argv[0]));

	for (i = 1; i < 501; i++) {
		sprintf(bWrite, "%03d", i);

		strcat(bWrite, "aaa");

		write(atoi(argv[1]), bWrite, 6);

		if (i % 100 == 0) usleep(100000);
	}
	exit(0);
}