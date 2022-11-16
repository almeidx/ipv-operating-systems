#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int status;
	if (fork()) { /* pai */
		printf("À espera...\n");
		wait(&status); /* bloqueio até que o filho termine */
		printf("O meu filho já terminou\n");
		printf("Terminou Status: exit:%d sinal:%d\n", status >> 8, status & 0xFF);
	} else { /* filho */
		printf("PF: PID=%d\n", getpid());
		sleep(15); /* para simular atividade */
		return 5;
	} /* valor a ser devolvido em status*/

	return 0;
}
