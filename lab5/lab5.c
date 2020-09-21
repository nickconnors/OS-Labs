#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int **A;
int **B;
int **C1;
int **C;
int n, m, p;

int threadID;

pthread_t tid[6];

sem_t mutex;

void *multiply(void*);

void allocateMatrices() {
	int i, j;

	/* Allocate n * m array */
	A = malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		A[i] = malloc(m * sizeof(int));
	}

	/* Allocate m * p array */
	B = malloc(m * sizeof(int*));
	for (i = 0; i < m; i++) {
		B[i] = malloc(p * sizeof(int));
	}

	/* Allocate two n * p arrays */
	C1 = malloc(n * sizeof(int*));
	C = malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) {
		C[i] = malloc(p * sizeof(int));
		C1[i] = malloc(p * sizeof(int));
	}

	/* Fill matrix A */
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			A[i][j] = i * j;
		}
	}

	/* Fill matrix B */
	for (i = 0; i < m; i++) {
		for (j = 0; j < p; j++) {
			B[i][j] = i + j;
		}
	}
}

void freeMatrices() {
	free(A);
	free(B);
	free(C);
	free(C1);
}

int compare() {
	int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < p; j++) {
            if (C1[i][j] != C[i][j]) {
                return 0; 
            }
        }
    }
    return 1;
}

void printComparison() {
	int result = compare();

	printf("Comparison: ");
	if (result == 1) {
		printf("No Error \n");
	} else {
		printf("Error \n");
	}
}

/* For testing/debugging */
void print_matrix(int **matrix, int r, int c) {
	int i, j;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void multithread_multiply(int numThreads) {
	struct timeval t0, t1;
	int i;

	threadID = 0;

	gettimeofday(&t0, NULL);

	for (i = 0; i < numThreads; i++) {
		pthread_create(&tid[i], NULL, multiply, &numThreads);
	}
	for (i = 0; i < numThreads; i++) pthread_join(tid[i], NULL);

	gettimeofday(&t1, NULL);

	printf("\n%d\t%.2f\n", numThreads, (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec)/1000000.0);
	printComparison();
}

int main() {
	struct timeval t0, t1;
	int i, j, k;
	printf("Enter n (<=6000), m (<=3000), p (<=1000): ");
	scanf("%d %d %d", &n, &m, &p);

	allocateMatrices();

	gettimeofday(&t0, NULL);

	for (i = 0; i < n; i++) {
		for (j = 0; j < p; j++) {
			C1[i][j] = 0;
			for (k = 0; k < m; k++) {
				C1[i][j] += A[i][k] * B[k][j]; 
			}
		}
	}

	gettimeofday(&t1, NULL);
	printf("\nn=%d,m=%d,p=%d\n", n, m, p);
	printf("Threads    Seconds\n");
	printf("1\t%.2f", (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec)/1000000.0);

	sem_init(&mutex, 0, 1);

	multithread_multiply(2);
	multithread_multiply(3);
	multithread_multiply(4);
	multithread_multiply(5);
	multithread_multiply(6);

	freeMatrices();
}

void *multiply(void *numThreads) {
	int i, j, k;

	sem_wait(&mutex);
	int thread = threadID++;
	sem_post(&mutex);

	for (i = thread * n / *((int*)numThreads); i < (thread + 1) * n / *((int*)numThreads); i++) {
		for (j = 0; j < p; j++) {
			C[i][j] = 0;
			for (k = 0; k < m; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	pthread_exit(NULL);
}