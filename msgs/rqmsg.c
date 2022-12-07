#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

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
	/*Remove fila de mensagens*/
	chave = atoi(argv[1]);
	id = msgget(chave, 0); /*Obter id*/
	exit_on_error(id, "Erro ao tentar obter o id da fila\n");
	printf("Fila de mensagens: chave=%d id=%d\n", chave, id);
	id = msgctl(id, IPC_RMID, NULL);
	exit_on_error(id, "Erro ao remover fila\n");
	printf("Fila removida\n");
}
