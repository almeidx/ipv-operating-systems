#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int i, pid_pai = getpid();

	for (i = 1; i <= 3; i++) {
		if (pid_pai == getpid()) {
			fork(); /* só o pai é que faz fork()*/
		}
	}

	if (pid_pai != getpid()) {
		printf("Proc. filho PID=(%d)\n", getpid());
	}

	return 0;
}
