#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	printf("PID:%d Parent PID:%d\n", getpid(), getppid());
	while (1)
		;

	return 0;
}
