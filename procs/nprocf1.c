#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	fork();
	fork();
	printf("Proc. %d (filho de %d)\n", getpid(), getppid());
	sleep(1); /*admitir que chega para nenhum pai
	 termine antes do filho fazer getppid() */

	return 0;
}
