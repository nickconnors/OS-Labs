/* Author: Nick Connors */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* thread routines */
void *first();
void *second();
void *third();
void *fourth();

pthread_t Thread1, Thread2, Thread3, Thread4; /* thread IDs */
sem_t mutex;

int Account[] = {100000, 100000, 100000}; /* Shared array */

int main() {

	sem_init(&mutex, 0, 1);

	pthread_create(&Thread1, NULL, first, NULL);
	pthread_create(&Thread2, NULL, second, NULL);
	pthread_create(&Thread3, NULL, third, NULL);

	pthread_join(Thread2, NULL);
	pthread_exit(NULL);
} /* end main */

void *first() {
	int i, internal_reg;

	pthread_create(&Thread4, NULL, fourth, NULL);

	for (i = 0; i < 10000; i++) {
		/* Transfer 200 from shared array slot 0 to slot 1 */
		sem_wait(&mutex);
		internal_reg = Account [0];
		internal_reg = internal_reg - 200;
		Account[0] = internal_reg;

		internal_reg = Account [1];
		internal_reg = internal_reg + 200;
		Account[1] = internal_reg;

		/* output contents of each account and
		their sum after 1,000th, 2,000th, 3,000th, .... and 10,000th iteration*/
		if ((i + 1) % 1000 == 0) {
 			printf("Thread 1:\nAccount 0: %d\n", Account[0]);
 			printf("Account 1: %d\n", Account[1]);
 			printf("Account 2: %d\n", Account[2]);
 			printf("Sum: %d\n\n", Account[0] + Account[1] + Account[2]);
 		}
 		if ((i + 1) % 3000 == 0) {
 				usleep(200000);
 		}
 		sem_post(&mutex);
	} 
	pthread_exit(NULL);
}

void *second() {
	int i, internal_reg;
	
	for (i = 0; i < 10000; i++) {
		sem_wait(&mutex);
		internal_reg = Account [1];
		internal_reg = internal_reg - 200;
		Account[1] = internal_reg;

		internal_reg = Account [2];
		internal_reg = internal_reg + 200;
		Account[2] = internal_reg;

		if ((i + 1) % 1000 == 0) {
 			printf("Thread 2:\nAccount 0: %d\n", Account[0]);
 			printf("Account 1: %d\n", Account[1]);
 			printf("Account 2: %d\n", Account[2]);
 			printf("Sum: %d\n\n", Account[0] + Account[1] + Account[2]);
 		}
 		if ((i + 1) == 2000 || (i + 1) == 4000 || (i + 1) == 2000 || (i + 1) == 9000) {
 				usleep(200000);
 		}
 		sem_post(&mutex);
	}
	pthread_exit(NULL);
}

void *third() {
	int i, internal_reg;
	
	for (i = 0; i < 10000; i++) {
		sem_wait(&mutex);
		internal_reg = Account [2];
		internal_reg = internal_reg - 200;
		Account[2] = internal_reg;

		internal_reg = Account [0];
		internal_reg = internal_reg + 200;
		Account[0] = internal_reg;

		if ((i + 1) % 1000 == 0) {
 			printf("Thread 3:\nAccount 0: %d\n", Account[0]);
 			printf("Account 1: %d\n", Account[1]);
 			printf("Account 2: %d\n", Account[2]);
 			printf("Sum: %d\n\n", Account[0] + Account[1] + Account[2]);
 		}
 		if ((i + 1) == 2000 || (i + 1) == 7500) {
 				usleep(300000);
 		}
 		sem_post(&mutex);
	}
	pthread_exit(NULL);
}

void *fourth() {
	int i, sum = 0, sum_check = 0, sum_not_equal = 0;

	for (i = 0; i < 50000; i++) {
 		sem_wait(&mutex);
 		sum = Account[0] + Account[1] + Account[2];
 		sum_check++;
 		if (sum != 300000) {
 			sum_not_equal++;
 		}
 		if (i % 10000 == 0) {
 				usleep(50000);
 			}
 		sem_post(&mutex);
 	}
 		printf("Thread 4:\nSum checked %d times.\n", sum_check);
 		printf("Sum not equal %d times.\n", sum_not_equal);

 		exit;
}

