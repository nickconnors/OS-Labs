#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int fd[2];
	int a, b, c, i, count, charsRead, charCount, readCount;
	char readBuffer[101];
	char bWrite[7];
	char cWrite[4];
	char letter;

	a = pipe(fd);

	b = fork();
	if (b == 0) {
		// close pipe reading
		close(fd[0]);

		//write to pipe
		for (i = 1; i < 501; i++) {
			// convert iteration number to 3-digit string
			sprintf(bWrite, "%03d", i);

			// concat iteration number with "aaa"
			strcat(bWrite, "aaa");

			// write string to pipe exluding null terminator
			write(fd[1], bWrite, 6);

			// sleep .1 seconds every 100 iterations
			if (i % 100 == 0) usleep(100000);
		}
		exit(0);
	}

	c = fork();
	if (c == 0) {
		close(fd[0]);

		// initialize letter to '@'
		letter = 64;
		count = 0;
		for (i = 1; i < 261; i++) {
			// letter range is A-Z
			letter++;
			if (letter == 91) {
				letter = 65;
				count++;
			}
			cWrite[0] = letter;
			cWrite[1] = 'x';
			sprintf(&cWrite[2], "%d", count);

			write(fd[1], cWrite, 3);

			if (i % 60 == 0) usleep(300000);
		}
		exit(0);
	}

	// close pipe writing
	close(fd[1]);

	memset(&readBuffer[0], '\0', sizeof(readBuffer));
	charCount = 0;
	readCount = 0;
	while ((charsRead = read(fd[0], readBuffer, 100)) > 0) {
		charCount += charsRead;
		readCount++;
		printf("%s\n", readBuffer);
		memset(&readBuffer[0], '\0', sizeof(readBuffer));

		if (readCount % 50 == 0) usleep(200000);
	}

	printf("Total reads: %d\nTotal characters read from pipe: %d\n", readCount, charCount);
}