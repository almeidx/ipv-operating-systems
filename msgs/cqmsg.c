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
#define PERMISSOES 0600 /* admita-se que serve para o exemplo */

int main(int argc, char *argv[]) {
	int chave, id;
	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}
	/*Cria fila de mensagens*/
	chave = atoi(argv[1]);
	id = msgget(chave, IPC_CREAT | PERMISSOES);
	/* Se é suposto não existir
	id=msgget(chave, IPC_CREAT | IPC_EXCL | PERMISSOES);*/
	exit_on_error(id, "Erro ao tentar criar a fila\n");
	printf("Fila de mensagens: chave=%d id=%d\n", chave, id);
}
