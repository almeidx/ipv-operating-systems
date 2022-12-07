#include "sem_funcoes.h"

#define PERMISSOES 0600

int main(int argc, char *argv[]) {
	int chave, id, v;

	/* Usage*/
	if (argc != 3) {
		printf("Usage: %s <chave> <valor inicial semáforo>\n", argv[0]);
		exit(1);
	}

	/* Cria semáforo */
	chave = atoi(argv[1]);
	v = atoi(argv[2]);
	id = sem_criar(chave, PERMISSOES, v);

	printf("Semáforo: chave=%d id=%d v=%d\n", chave, id, v);
}
