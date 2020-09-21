/* Author: Nick Connors
   Compilation command: make
*/

#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num;
	char str[4];
} element;

element *BufferA = NULL;
element *BufferB = NULL;
element *BufferC = NULL;


int main() {
	int outA = 0, outB = 0, outC = 0, i;

	/* Create semaphores */
	int BufferAEmpty = sem_create(100000, 20);
	int BufferBEmpty = sem_create(200000, 30);
	int BufferCEmpty = sem_create(300000, 25);
	int BufferAFull = sem_create(110000, 0);
	int BufferBFull = sem_create(220000, 0);
	int BufferCFull = sem_create(330000, 0);
	int s1 = sem_create(111111, 0);
	int s2 = sem_create(222222, 0);
	int s3 = sem_create(333333, 0);

	/* create shared memory buffers */
	int shm_arrA = shm_get(111000, (void**)&BufferA, 20*sizeof(element));
	int shm_arrB = shm_get(222000, (void**)&BufferB, 30*sizeof(element));
	int shm_arrC = shm_get(333000, (void**)&BufferC, 25*sizeof(element));


	for (i = 0; i < 500; i++) {
		sem_wait(BufferAFull);
		sem_wait(BufferBFull);
		sem_wait(BufferCFull);
		printf("%d%s ", BufferA[outA].num, BufferA[outA].str);
		printf("%s%d ", BufferB[outB].str, BufferB[outB].num);
		printf("%d%s ", BufferC[outC].num, BufferC[outC].str);
		sem_signal(BufferAEmpty);
		sem_signal(BufferBEmpty);
		sem_signal(BufferCEmpty);

		outA = (outA + 1) % 20;
		outB = (outB + 1) % 30;
		outC = (outC + 1) % 25;

		if (i % 100 == 0) {
			usleep(300000);
		}
 				
	}

	printf("\n");

}