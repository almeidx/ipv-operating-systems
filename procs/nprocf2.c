#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int i;
	for (i = 1; i <= 3; i++)
		fork();
	printf("Proc. PID=(%d)\n", getpid());

	return 0;
}
