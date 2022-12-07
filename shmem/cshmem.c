#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */

int main(int argc, char *argv[]) {
	int chave, id, tamanho;

	/*Usage*/
	if (argc != 3) {
		printf("Usage: %s <chave> <tamanho>\n", argv[0]);
		exit(1);
	}

	/*Cria memória partilhada*/
	chave = atoi(argv[1]);
	tamanho = atoi(argv[2]);
	id = shmget(chave, tamanho, IPC_CREAT | PERMISSOES);

	/* Se é suposto não existir
	id=shmget(chave, IPC_CREAT | IPC_EXCL | PERMISSOES);*/
	exit_on_error(id, "Erro ao tentar criar a mem. partilhada\n");

	printf("Mem. Partilhada: chave=%d id=%d\n", chave, id);
}
