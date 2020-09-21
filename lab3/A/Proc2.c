#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>

int *Account = NULL;

int main() {
	int i, internal_reg;

	//synchronize with Proc1, Proc3 & Proc4 (4 process 4 way sync.)
	int s1 = sem_open(111111);
	int s2 = sem_open(222222);
	int s3 = sem_open(333333);
	int s4 = sem_open(444444);
	int mutex = sem_open(555555);

	int shm_arr = shm_get(123456, (void**)&Account, 3*sizeof(int));

	sem_signal(s1);
	sem_signal(s3);
	sem_signal(s4);
	sem_wait(s2);
 	sem_wait(s2);
 	sem_wait(s2);

 	for (i = 0; i < 2000; i++) {
 		sem_wait(mutex);
 		internal_reg = Account [1];

 		/*take from Account[1]*/
 		internal_reg = internal_reg - 200;
 		Account[1] = internal_reg;

 		/* same thing, except we're adding $200 to Account[2] now... */
 		/*Proc3 adds into Account[0]*/
 		internal_reg = Account [2];
 		internal_reg = internal_reg + 200;
 		Account[2] = internal_reg;

 		if (i % 100 == 0) {
 			printf("Account 0: %d\n", Account[0]);
 			printf("Account 1: %d\n", Account[1]);
 			printf("Account 2: %d\n", Account[2]);
 			printf("Sum: %d\n", Account[0] + Account[1] + Account[2]);

 			if (i % 400 == 0) {
 				usleep(200000);
 			}
 		}
 		sem_signal(mutex);
 	}
 /* Add a code that prints contents of each account
 and their sum after 100th, 200th, 300th, .... and 1900th
 iteration*/
}
/*in the code above include some wait and signal operations on
semaphores. Do not over-synchronize. */