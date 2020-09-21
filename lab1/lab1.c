/* Compilation Command:
	gcc -ansi -g lab1.c -o lab1
*/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void replace_each_i_with_X(char *buffer) {
	int i = 0;
	while (buffer[i] != '\0') {
		if (buffer[i] == 'i') buffer[i] = 'X';
		i++;
	}
}

void replace_each_m_with_W(char *buffer) {
	int i = 0;
	while (buffer[i] != '\0') {
		if (buffer[i] == 'm') buffer[i] = 'W';
		i++;
	}
}

void print_buffer(char *buffer, int n) {
	int i = 0;
	while (i < n) {
		printf("%c", buffer[i]);
		i++;
	}
	printf("\n");
}

int main() {

	int a, b, c, bytesWritten, closed, maxReads, remainingBytes;
	int offset = 0;
	int bytesRead = 1;
	int it = 1;
	int readCount = 0;
	int writeCount = 0;
	int writeCount2 = 0;
	char buffer[300];
	char buff[1];
	char *blank = "                    ";
	char *overwrite =  "12345678abcdefgh";
	char insert[] = "1111abcdefghijklmnopQRSTUVWXYZ";
	char name[] = "Nick Connors";

	/* Part 1 */

	/* Open TestFile from downloads */
	a = open("/home/nick/Downloads/TestFile.dat", O_RDONLY);
	if (a < 0) {
		printf("Error opening file TestFile.dat %s\n", strerror(errno));
		return 0;
	}

	/* Create XYZ in current directory with read and write access*/
	b = open("XYZ", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (b < 0) {
		printf("Error creating file XYZ. %s\n", strerror(errno));
		return 0;
	}	


	/* 1a) Read 150 characters at a time from TestFile and increase readCount */
	while (bytesRead > 0) {
		bytesRead = read(a, buffer, 150);
		readCount+= bytesRead;

		/* 1b) Write characters read immediately into XYZ and increase writeCount*/
		bytesWritten = write(b, buffer, bytesRead);
		if (bytesWritten < 0) {
			printf("Error writing to file XYZ. %s\n", strerror(errno));
			return 0;
		}
		writeCount += bytesWritten;
		/* 1c) Write string of 20 blank characters into XYZ and increase writeCount */
		bytesWritten = write(b, blank, 20);
		if (bytesWritten < 0) {
			printf("Error writing to file XYZ. %s\n", strerror(errno));
			return 0;
		}
		writeCount += bytesWritten;
	}

	if (bytesRead < 0) {
		printf("Error reading from TestFile.dat %s\n", strerror(errno));
		return 0;
	}	

	/* Display numbers of characters read from TestFile and number of characters written to XYZ */
	printf("Characters read from TestFile.dat: %d\n", readCount);
	printf("Characters written to XYZ: %d\n\n", writeCount);

	closed = close(a);
	if (closed < 0)	{
		printf("Error closing file TestFile.dat %s\n", strerror(errno));
		return 0;
	}	

	/* Part 2 */

	writeCount = 0;

	/* Create XXX and WWW with read and write access*/
	a = open("XXX", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (a < 0) {
		printf("Error creating file XXX. %s\n", strerror(errno));
		return 0;
	}
	c = open("WWW", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (c < 0) {
		printf("Error creating file WWW. %s\n", strerror(errno));
		return 0;
	}	

	/* Point to beginning of XYZ before read */
	if (lseek(b, 0, SEEK_SET) < 0) {
		printf("Error offsetting XYZ pointer. %s\n", strerror(errno));
		return 0;
	}

	/* 2a) Read the next 120 characters from XYZ */
	while ((bytesRead = read(b, buffer, 120)) > 0) {
		
		/* 2a) Replace each character 'i' with character 'X' and write all 120 characters to XXX */
		replace_each_i_with_X(buffer);
		bytesWritten = write(a, buffer, bytesRead);
		if (bytesWritten < 0) {
			printf("Error writing to file XXX. %s\n", strerror(errno));
			return 0;
		}
		writeCount += bytesWritten;

		/* 2b) Read the next 100 characters from XYZ */
		bytesRead = read(b, buffer, 100);
		if (bytesRead < 0) {
			printf("Error reading from XYZ. %s\n", strerror(errno));
			return 0;
		} else if (bytesRead > 0) {
			/* 2b) Replace each character 'm' with character 'W' and write all 100 characters to WWW */
			replace_each_m_with_W(buffer);
			bytesWritten = write(c, buffer, bytesRead);
			if (bytesWritten < 0) {
				printf("Error writing to file WWW. %s\n", strerror(errno));
				return 0;
			}
			writeCount2 += bytesWritten;
		}
	}

	if (bytesRead < 0) {
		printf("Error reading from XYZ. %s\n", strerror(errno));
		return 0;
	}

	/* Display number of characters written to XXX and in WWW */
	printf("Characters written to XXX: %d\n", writeCount);
	printf("Characters written to WWW: %d\n\n", writeCount2); 

	/* Delete XYZ */
	if (unlink("XYZ") < 0)	{
		printf("Error deleting file XYZ. %s\n", strerror(errno));
		return 0;
	}	

	/* Part 3 */

	/* Point to position 1000 of XXX */
	if (lseek(a, 1000, SEEK_SET) < 0) {
		printf("Error offsetting XXX pointer. %s\n", strerror(errno));
		return 0;
	}

	/* Overwrite characters in XXX starting at position 1000 with overwrite string */
	if (write(a, overwrite, 16) < 0) {
		printf("Error overwriting file XXX. %s\n", strerror(errno));
		return 0;
	}

	/* Part 4 */

	/* Append file WWW with string name */
	if ((bytesWritten = write(c, name, sizeof(name) - 1)) < 0) {
		printf("Error appending file WWW with name. %s\n", strerror(errno));
		return 0;
	}

	/* Add size of string to total number of bytes written to WWW */
	writeCount2 += bytesWritten;

	/* Part 5 */
    
	if ((writeCount2 - 500) % sizeof(buffer) != 0) {
		maxReads = ((writeCount2 - 500) / sizeof(buffer)) + 1;
	} else {
		maxReads = ((writeCount2 - 500) / sizeof(buffer));
	}
	
    /* Insert the string insert after positon 500 of file WWW*/
	while (it < maxReads + 1) {
		if (it != maxReads || maxReads * sizeof(buffer) == writeCount2 - 500) {
            if ((offset = lseek(c, -(sizeof(buffer)), SEEK_CUR)) < 0) break;
            if ((bytesRead = read(c, buffer, sizeof(buffer))) < 0) break;
            if ((offset = lseek(c, -(sizeof(buffer)) + (sizeof(insert) - 1), SEEK_CUR)) < 0) break;
            if ((bytesWritten = write(c, buffer, sizeof(buffer))) < 0) break;
            if ((offset = lseek(c, -(sizeof(buffer)) - (sizeof(insert) - 1), SEEK_CUR)) < 0) break;
		} else {
			remainingBytes = (writeCount2 - 500) - (sizeof(buffer) * (maxReads - 1));
            if ((offset = lseek(c, remainingBytes / -1, SEEK_CUR)) < 0) break;
            if ((bytesRead = read(c, buffer, remainingBytes)) < 0) break;
            if ((offset = lseek(c, (remainingBytes / -1) + (sizeof(insert) - 1), SEEK_CUR)) < 0) break;
            if ((bytesWritten = write(c, buffer, remainingBytes)) < 0) break;
            if ((offset = lseek(c, (remainingBytes / -1) - (sizeof(insert) - 1), SEEK_CUR)) < 0) break;
			writeCount2 += write(c, insert, (sizeof(insert) - 1));
			
		}
		it++;
	}
    
    if (offset < 0) {
        printf("Error offsetting WWW pointer. %s\n", strerror(errno));
        return 0;
    } else if (bytesRead < 0) {
        printf("Error reading file WWW. %s\n", strerror(errno));
        return 0;
    } else if (bytesWritten < 0) {
        printf("Error writing to file WWW. %s\n", strerror(errno));
        return 0;
    }

	/* Part 6 */
    
    /* Create new file ZZZ with read and write access*/
	b = open("ZZZ", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (b < 0) {
        printf("Error creating file ZZZ. %s\n", strerror(errno));
        return 0;
    }

	if (lseek(a, 0, SEEK_SET) < 0) {
		printf("Error offsetting WWW pointer. %s\n", strerror(errno));
		return 0;
	}
	
	while ((bytesRead = read(a, buffer, 300)) > 0) {

		bytesWritten = write(b, buffer, bytesRead);
		if (bytesWritten < 0) {
			printf("Error writing to file ZZZ. %s\n", strerror(errno));
			return 0;
		}
	}
	
	if (bytesRead < 0) {
		printf("Error reading from WWW %s\n", strerror(errno));
		return 0;
	}

	/* Part 7 */
	
    /* Append file ZZZ with file WWW, but by writing it in reverse order */
	it = 1;
	int newCount = 0;
	offset = lseek(c, 0, SEEK_END);
	while (offset > 0) {
        if ((offset = lseek(c, -(it), SEEK_END)) < 0) break;
        if ((bytesRead = read(c, buff, 1) < 0)) break;
        if ((bytesWritten = write(b, buff, 1)) < 0) break;
		writeCount++;
		it++;
	}
    
    if (offset < 0) {
        printf("Error offsetting WWW pointer. %s\n", strerror(errno));
        return 0;
    } else if (bytesRead < 0) {
        printf("Error reading file WWW. %s\n", strerror(errno));
        return 0;
    } else if (bytesWritten < 0) {
        printf("Error writing to file ZZZ. %s\n", strerror(errno));
        return 0;
    }

    /* Display total number of characters in ZZZ */
	printf("Total characters written to ZZZ: %d\n\n", writeCount);

	/* Part 8 */

    if (lseek(b, 0, SEEK_SET) < 0) {
        printf("Error offsetting ZZZ pointer. %s\n", strerror(errno));
        return 0;
    }
    
    /* Read 80 characters at a time from ZZZ and display every 100th set of 80*/
	bytesRead = 80;
	it = 0;
	while (bytesRead ==  80) {
		if ((bytesRead = read(b, buffer, 80)) < 0) break;
		it++;
		if (it == 100) {
			print_buffer(buffer, 80);
			it = 0;
		}
	}
    
    if (bytesRead < 0) {
        printf("Error reading file ZZZ. %s\n", strerror(errno));
        return 0;
    }
    
    /* Delete XXX, WWW and ZZZ */
	if (unlink("XXX") < 0)	{
		printf("Error deleting file XXX. %s\n", strerror(errno));
		return 0;
	}
	if (unlink("WWW") < 0)	{
		printf("Error deleting file WWW. %s\n", strerror(errno));
		return 0;
	}
	if (unlink("ZZZ") < 0)	{
		printf("Error deleting file ZZZ. %s\n", strerror(errno));
		return 0;
	}
	
}
