#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
/* Part 2 */

	int read_file, write_file;
	char buffer[200];

	/* Open TestFile.dat for reading */
	if ((read_file = open("/home/nick/Downloads/TestFile.dat", O_RDONLY)) < 0) printf("Error 1\n");

	/* Create XYZ.txt */
	if ((write_file = open("XYZ.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0) printf("Error 2\n");

	/* Write last 200 characters from TestFile.dat to XYZ.txt */
	if ((lseek(read_file, -201, SEEK_END)) < 0) printf("Error 3\n");
	if ((read(read_file, buffer, 200)) < 0) printf("Error 4\n");
	write(write_file, buffer, 200);

	printf("Pid %d Code BB: Creating file XYZ.txt and write 200 characters from TestFile.dat\n", getpid());

	close(read_file);
	close(write_file);

	printf("Pid %d Code BB: Done and terminating\n", getpid());
	exit(0);

}

