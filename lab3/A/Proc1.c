/* Author: Nick Connors
   Compilation command: make
*/

#include "ssem.h"
#include "sshm.h" 
#include <unistd.h>
#include <stdio.h>

int *Account = NULL;

int main() {
	int i, internal_reg;
	/* here create and initialize all semaphores */
	int s1 = sem_create(111111, 0);
	int s2 = sem_create(222222, 0);
	int s3 = sem_create(333333, 0);
	int s4 = sem_create(444444, 0);
	int mutex = sem_create(555555, 1);

	/* here created: shared memory array Account of size 3 */
	int shm_arr = shm_get(123456, (void**)&Account, 3*sizeof(int));

 	Account[0]=10000;
 	Account[1]=10000;
 	Account[2]=10000;

	/* synchronize with Proc2, Proc3 and Proc4 (4 process 4 way
	synch.)*/
	sem_signal(s2);
	sem_signal(s3);
	sem_signal(s4);
	sem_wait(s1);
 	sem_wait(s1);
 	sem_wait(s1);

 	for (i = 0; i < 2000; i++) { 
 		sem_wait(mutex);
 		internal_reg = Account [0];
 		internal_reg = internal_reg - 200;
 		Account[0] = internal_reg;

 		/* same thing, except we're adding $200 to account1 now... */
 		internal_reg = Account [1];
 		internal_reg = internal_reg + 200;
 		Account[1] = internal_reg;

 		if (i % 100 == 0) {
 			printf("Account 0: %d\n", Account[0]);
 			printf("Account 1: %d\n", Account[1]);
 			printf("Account 2: %d\n", Account[2]);
 			printf("Sum: %d\n", Account[0] + Account[1] + Account[2]);

 			if (i % 600 == 0) {
 				usleep(200000);
 			}
 		}
 		sem_signal(mutex);
 	}

 	sem_rm(s1);
 	sem_rm(s2);
 	sem_rm(s3);
 	sem_rm(s4);
 	sem_rm(mutex);

 	shm_rm(shm_arr);
 	/* Add a code that prints contents of each account and
 	their sum after 100th, 200th, 300th, .... and 1900th
 	iteration*/
 }
/*in the code above include some wait and signal operations on
semaphores. Do not over-synchronize. */ 