#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	char buffer;
	int byteRead = 1;
	
	/* Part 6: Read XYZ.txt character by character and print as read*/
	int XYZ = open("XYZ.txt", O_RDONLY);
	printf("Pid %d Code EE: This is what I have read from XYZ.txt:\n", getpid());
	while (byteRead == 1) {
		byteRead = read(XYZ, &buffer, 1);
		if (byteRead == 1) printf("%c", buffer);
	}
	printf("\n");

	/* Delete file */
	unlink("XYZ.txt");

	printf("Pid %d Code EE: Deleted XYZ.txt and I am terminating\n", getpid());
	exit(0);
}
