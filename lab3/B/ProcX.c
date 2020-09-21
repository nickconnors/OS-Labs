#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int num;
	char str[4];
} element;

element *BufferA = NULL;

int main() {
	int in = 0, i = 0;


	int BufferAEmpty = sem_open(100000);
	int BufferAFull = sem_open(110000);
	int s1 = sem_open(111111);
	int s2 = sem_open(222222);
	int s3 = sem_open(333333);

	int shm_arrA = shm_get(111000, (void**)&BufferA, 20*sizeof(element));

		sem_signal(s2);
		sem_signal(s3);
		sem_wait(s1);
 		sem_wait(s1);

	for (i = 0; i < 500; i++) {
		sem_wait(BufferAEmpty);
		BufferA[in].num = i + 1;
		strcpy(BufferA[in].str, "xx");
		in = (in + 1) % 20;
		sem_signal(BufferAFull);

		if (i % 100 == 0) {
			usleep(300000);
		}
	}

	sem_rm(100000);
	sem_rm(200000);
	sem_rm(300000);
	sem_rm(110000);
	sem_rm(220000);
	sem_rm(330000);
	sem_rm(111111);
	sem_rm(222222);
	sem_rm(333333);

	shm_rm(111000);
	shm_rm(222000);
	shm_rm(333000);
}