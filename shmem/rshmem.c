#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main(int argc, char *argv[]) {
	int chave, id;

	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*Remove segmento de mem. partilhada*/
	chave = atoi(argv[1]);
	id = shmget(chave, 0, 0); /*Obter id*/
	exit_on_error(id, "Erro ao tentar obter o id do segmento\n");

	printf("Mem. partilhada: chave=%d id=%d\n", chave, id);

	id = shmctl(id, IPC_RMID, NULL);
	exit_on_error(id, "Erro ao remover o segmento\n");

	printf("Segmento removido\n");
}
