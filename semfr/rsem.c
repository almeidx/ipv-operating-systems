#include "sem_funcoes.h"

int main(int argc, char *argv[]) {
	int chave, id;

	/* Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	chave = atoi(argv[1]);
	id = sem_id(chave); /* Obtém id */

	sem_remover(id);

	printf("Semáforo removido : chave=%d id=%d\n", chave, id);
}
