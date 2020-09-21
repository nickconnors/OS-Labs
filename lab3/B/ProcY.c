#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	int num;
	char str[4];
} element;

element *BufferB = NULL;

int main() {
	element y;
	int in = 0, i = 0;

	int BufferBEmpty = sem_open(200000);
	int BufferBFull = sem_open(220000);
	int s1 = sem_open(111111);
	int s2 = sem_open(222222);
	int s3 = sem_open(333333);

	int shm_arrA = shm_get(222000, (void**)&BufferB, 30*sizeof(element));


	sem_signal(s1);
	sem_signal(s3);
	sem_wait(s2);
 	sem_wait(s2);

	for (i = 0; i < 500; i++) {
		sem_wait(BufferBEmpty);
		BufferB[in].num = i + 1;
		strcpy(BufferB[in].str, "YYY");
		in = (in + 1) % 30;
		sem_signal(BufferBFull);

		if (i % 75 == 0) {
			usleep(300000);
		}
	}

}