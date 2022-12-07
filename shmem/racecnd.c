#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define TEMPOMAX 3
#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int aleatorio(int de, int ate) { /*Devolve um valor aleatorio entre 'de' e 'ate'*/
	return de + (int)(((double)(ate - de + 1)) * rand() / (RAND_MAX + 1.0));
}

void acede(int *p) {
	int j, k1, k2;
	srand(getpid());
	// ii = 1;
	for (j = 0; j < 10; j++) {
		/* início da secção crítica !!!*/
		k1 = *p; /* coloca em k o valor que está na memória */
		*p = k1 + 1;
		/* para aumentar a probabilidade de dar "asneira" */
		sleep(aleatorio(0, TEMPOMAX));
		k2 = *p; /* supostamente, estar-se-ia a somar 1 a *p */
		/* fim da secção crítica */
		printf("(%d:) %d+1= %d\n", getpid(), k1, k2);
	}
}

int main() {
	int pai, id, *i;
	id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
	exit_on_error(id, "Erro ao criar o segmento de memória");
	i = (int *)shmat(id, NULL, 0);
	*i = 0;
	printf("Este programa vai imprimir contas eventualmente erradas\n");
	printf("Ilustra os problemas de concorrência\n");
	pai = getpid();
	fork();
	acede(i); /* pai e filho executam esta função, concorrentemente */
	shmdt(i);
	if (getpid() == pai) {
		wait(NULL);
		shmctl(id, IPC_RMID, 0);
	}
}
