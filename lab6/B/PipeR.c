#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	int charsRead, charCount, readCount;
	char readBuffer[101];

	close(atoi(argv[1]));

	memset(&readBuffer[0], '\0', sizeof(readBuffer));
	charCount = 0;
	readCount = 0;
	while ((charsRead = read(atoi(argv[0]), readBuffer, 100)) > 0) {
		charCount += charsRead;
		readCount++;
		printf("%s\n", readBuffer);
		memset(&readBuffer[0], '\0', sizeof(readBuffer));

		if (readCount % 50 == 0) usleep(200000);
	}

	printf("Total reads: %d\nTotal characters read from pipe: %d\n", readCount, charCount);
	exit(0);
}