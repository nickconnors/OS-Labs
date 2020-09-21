/* Author: Nick Connors */

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* thread routines */
void *first();
void *second();
void *third();

pthread_t ThreadA, ThreadB, ThreadC; /* thread IDs */
sem_t mutex, BufferXEmpty, BufferYEmpty, BuffersFull;

typedef struct {
	int num;
	char str[5];
} element;

/* shared variables */
element BufferX[20];
element BufferY[40];
int A = 0;


int main() {

	sem_init(&mutex, 0, 1);
	sem_init(&BufferXEmpty, 0, 20);
	sem_init(&BufferYEmpty, 0, 40);
	sem_init(&BuffersFull, 0, 0);

	pthread_create(&ThreadA, NULL, first, NULL);
	pthread_create(&ThreadB, NULL, second, NULL);
	pthread_create(&ThreadC, NULL, third, NULL);

	pthread_join(ThreadC, NULL);
}

void *first() {
	int i, in = 0;

	for (i = 0; i < 3000; i++) {
		sem_wait(&BufferXEmpty);
		BufferX[in].num = i + 1;
		if ((i + 1) % 2 == 0) {
			strcpy(BufferX[in].str, "ABCaa");
		} else strcpy(BufferX[in].str, "XYZxx");
		sem_wait(&mutex);
		A ++;
		sem_post(&mutex);
		sem_post(&BuffersFull);

		in = (in + 1) % 20;

		if ((i + 1) % 500 == 0) {
			usleep(100000);
		}
	}
	pthread_exit(NULL);
}

void *second() {
	int i, in = 0;

	for (i = 0; i < 4000; i++) {
		sem_wait(&BufferYEmpty);
		BufferY[in].num = i + 1;
		if (i < 2000) {
			strcpy(BufferY[in].str, "MMM");
		} else strcpy(BufferY[in].str, "NNN");
		sem_post(&BuffersFull);

		in = (in + 1) % 40;

		if ((i + 1) % 1000 == 0) {
			usleep(200000);
		}
	}
	pthread_exit(NULL);
}

void *third() {
	int outX = 0, outY = 0, i;

	for (i = 0; i < 7000; i++) {
		sem_wait(&BuffersFull);
		if (A > 0) {
			printf("%d%s ", BufferX[outX].num, BufferX[outX].str);
			outX = (outX + 1) % 20;
			sem_wait(&mutex);
			A--;
			sem_post(&mutex);
			sem_post(&BufferXEmpty);
		} else {
			printf("%d%s ", BufferY[outY].num, BufferY[outY].str);
			outY = (outY + 1) % 40;
			sem_post(&BufferYEmpty);
		}

		if ((i + 1) % 2000 == 0) {
			usleep(300000);
		}
	}
	printf("\n");
	pthread_exit(NULL);
}