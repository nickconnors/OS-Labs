#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int i, count;
	char letter;
	char cWrite[4];

	close(atoi(argv[0]));

	letter = 64;
	count = 0;
	for (i = 1; i < 261; i++) {
		letter++;
		if (letter == 91) {
			letter = 65;
			count++;
		}
		cWrite[0] = letter;
		cWrite[1] = 'x';
		sprintf(&cWrite[2], "%d", count);

		write(atoi(argv[1]), cWrite, 3);

		if (i % 60 == 0) usleep(300000);
	}
		exit(0);
}