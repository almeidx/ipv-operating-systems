#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main() {
	int chave, id, *i;

	id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);
	exit_on_error(id, "Erro ao criar memória partilhada");

	i = (int *)shmat(id, NULL, 0);

	/* o pai aguarda que a memória tenha 1 para dizer "ping";
	 o filho aguarda que tenha 0 para dizer "pong" */
	*i = 1; /* para começar o "ping" */

	if (fork()) { /*Pai*/
		while (1) {
			while (*i != 1)
				; /* espera activa*/
			printf("Ping!\n");
			*i = 0; /* "autoriza" o outro processo */
		}
	} else { /*Filho*/
		while (1) {
			while (*i != 0)
				; /* espera activa*/
			printf("Pong!\n");
			*i = 1; /* "autoriza" o outro processo */
		}
	}
}
