#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int pid, status;

	if (!(pid = fork())) { /* filho */
		sleep(1);		   /* assumir que chega */
	} else {			   /* pai */
		while (waitpid(pid, &status, WNOHANG) != pid) {
			printf("Ainda não terminou !!\n");
		}

		printf("Terminou (PID=%d) (Status=%d)\n", pid, status);
	}

	return 0;
}
