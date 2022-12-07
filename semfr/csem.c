#include "sem_funcoes.h"

#define PERMISSOES 0600

int main(int argc, char *argv[]) {
	int chave, id, n;

	/* Usage*/
	if (argc != 3) {
		printf("Usage: %s <chave> <numero de semáforos>\n", argv[0]);
		exit(1);
	}

	/* Cria semáforo */
	chave = atoi(argv[1]);
	n = atoi(argv[2]);
	id = sem_criar_n(chave, n, PERMISSOES);

	printf("Semáforo: chave=%d id=%d\n", chave, id);
}
