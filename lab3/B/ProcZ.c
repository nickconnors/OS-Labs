#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int num;
	char str[4];
} element;

element *BufferC = NULL;

int main() {;
	int in = 0, i = 0;

	int BufferCEmpty = sem_open(300000);
	int BufferCFull = sem_open(330000);
	int s1 = sem_open(111111);
	int s2 = sem_open(222222);
	int s3 = sem_open(333333);

	int shm_arrA = shm_get(333000, (void**)&BufferC, 25*sizeof(element));

		sem_signal(s1);
		sem_signal(s2);
		sem_wait(s3);
 		sem_wait(s3);

	for (i = 0; i < 500; i++) {
		sem_wait(BufferCEmpty);
		BufferC[in].num = i + 1;
		strcpy(BufferC[in].str, "zz");
		in = (in + 1) % 25;
		sem_signal(BufferCFull);

		if (i % 60 == 0) {
			usleep(300000);
		}
	}

}