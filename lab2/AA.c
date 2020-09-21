#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

/* Compilation command: make */

int main() {
	
	int process_B, process_C1, process_C1a, process_D, process_C2, process_E, process_F;
	char *arg[1] = {0};
	int status;
	int XX;
	char sXX[12];
	char string[20];
	char *argv[4] = {string, sXX, "Nick Connors", 0};
	int process_A = getpid();

	/* Part 1: Create 3 processes, B, C1 and C1a */
	process_B = fork();
	if (process_B == 0) {
		execv("BB", arg);
	}

	process_C1 = fork();
	if (process_C1 == 0) {
		execv("CC", arg);
	}

	process_C1a = fork();
	if (process_C1a == 0) {
		execv("CC", arg);
	}

	printf("Pid %d Code AA: Created process Pid %d(code BB), process Pid %d(code CC) and process Pid %d(code CC)\n", process_A, process_B, process_C1, process_C1a);

	/* Wait for child to terminate */
	printf("Pid %d Code AA: Process Pid %d terminated.\n", process_A, wait(&status));

	/* Part 5: Create 3 processes, D, C2 and EE */
	process_D = fork();
	if (process_D == 0) {
		execv("DD", arg);
	}

	process_C2 = fork();
	if (process_C2 == 0) {
		execv("CC", arg);
	}

	process_E = fork();
	if (process_E == 0) {
		execv("EE", arg);
	}
	
	printf("Pid %d Code AA: Created process Pid %d(code DD), process Pid %d(code CC) and process Pid %d(code EE)\n", process_A, process_D, process_C2, process_E);

	/* Wait for process A to terminate */
	printf("Pid %d Code AA: Process Pid %d terminated (not D process)\n", process_A, wait(&status));
	
	/* Wait for process D to terminate */
	printf("Pid %d Code AA: Process Pid %d terminated.\n", process_A, waitpid(process_D, &status, 0));

	/* Part 10: Kill processes C1, C1a and C2 */
	printf("Pid %d Code AA: Killing process %d, Process Pid %d and Process Pid %d\n", process_A, process_C1, process_C1a, process_C2);
	if (kill(process_C1, SIGKILL) == 0) {
		printf("Pid %d Code AA: Process Pid %d terminated\n", process_A, process_C1);
	}
	if (kill(process_C1a, SIGKILL) == 0) {
		printf("Pid %d Code AA: Process Pid %d terminated\n", process_A, process_C1a);
	}
	if (kill(process_C2, SIGKILL) == 0) {
		printf("Pid %d Code AA: Process Pid %d terminated, and now waiting for 0.25 seconds\n", process_A, process_C2);
	}

	/* wait 0.25 sec */
	usleep(250000);
	printf("Pid %d Code AA: 0.25 sec elapsed\n", process_A);

	/* Part 11: Prompt for string and int */
	printf("Pid %d Code AA: input a character string:\t", process_A);
	scanf("%[^\n]", string);
	printf("Pid %d Code AA: input an integer:\t", process_A);
	scanf("%d", &XX);

	/* Convert int to string */
	sprintf(sXX, "%d", XX);

	/* Part 12: Create process F */
	process_F = fork();
	if (process_F == 0) {
		execv("FF", argv);
	}
	
	printf("Pid %d Code AA: Created process Pid %d(code FF) and terminating\n", process_A, process_F);

	exit(0);

}
