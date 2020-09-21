#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int main() {
	int process_C3, process_ps;
	char *arg[1] = {0};
	int status;
	int process_D = getpid();

	/* Part 7: Create process C3 */
	process_C3 = fork();
	if (process_C3 == 0) {
		execv("CC", arg);
	}
	printf("Pid %d Code DD: Created process Pid %d(code CC) and waiting for .5 seconds\n", process_D, process_C3);
	/* Wait for 0.5 sec */
	usleep(500000);

	/* Part 8: execute ps command */
	process_ps = fork();
	if (process_ps == 0) {
		execlp("/bin/ps","ps", "-u", "nick", 0);
	}
	printf("Pid %d Code DD: 0.5 sec elapsed. Created process %d(ps), and waiting for it to terminate\n", process_D, process_ps);

	/* Part 9: Wait for process D to terminate */
	printf("Pid %d Code DD: Process Pid %d terminated\n", process_D, wait(&status));
	
	printf("Pid %d Code DD: Killing Process Pid %d\n", process_D, process_C3);

	/* Kill process C3 */
	if (kill(process_C3, SIGKILL) == 0) {
		printf("Pid %d Code DD: Process Pid %d terminated\n", process_D, process_C3);
	}

	printf("Pid %d Code DD: Terminating\n", process_D);
	exit(0);
}
