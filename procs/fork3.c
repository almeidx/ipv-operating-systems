#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int pid;

	printf("E vai um\n");

	pid = fork();

	if (pid != 0) {
		/* processo pai*/
		printf("Sou o processo pai. Criei um processo filho\n");
	} else {
		/* processo filho*/
		printf("Sou um novo processo. Chamem-me filho\n");
	}

	printf("E vão dois\n");

	return 0;
}
