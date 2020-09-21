#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>

int *Account = NULL;

int main() {
	int i;
	int sum = 0, sum_check = 0, sum_not_equal = 0;

	//synchronize with Proc1, Proc3 & Proc4 (4 process 4 way sync.)
	int s1 = sem_open(111111);
	int s2 = sem_open(222222);
	int s3 = sem_open(333333);
	int s4 = sem_open(444444);
	int mutex = sem_open(555555);

	int shm_arr = shm_get(123456, (void**)&Account, 3*sizeof(int));

	sem_signal(s1);
	sem_signal(s2);
	sem_signal(s3);
	sem_wait(s4);
 	sem_wait(s4);
 	sem_wait(s4);

 	for (i = 0; i < 5000; i++) {
 		sem_wait(mutex);
 		sum = Account[0] + Account[1] + Account[2];
 		printf("Sum: %d\n", sum);
 		sum_check++;
 		if (sum != 30000) {
 			sum_not_equal++;
 		}
 		if (i % 1000 == 0) {
 				usleep(5000000);
 			}
 		sem_signal(mutex);
 	}
 		printf("Sum checked %d times.\n", sum_check);
 		printf("Sum not equal %d times.\n", sum_not_equal);
 }