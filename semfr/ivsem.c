#include "sem_funcoes.h"

int main(int argc, char *argv[]) {
	int chave, id, i, v;

	/* Usage*/
	if (argc != 4) {
		printf("Usage: %s <chave> <índice> <valor inicial>\n", argv[0]);
		exit(1);
	}

	chave = atoi(argv[1]);
	i = atoi(argv[2]);
	v = atoi(argv[3]);

	id = sem_id(chave); /* Obtém id */
	printf("Semáforo: chave=%d id=%d índice=%d\n", chave, id, i);

	sem_ini_var_n(id, i, v); /* Inicializa variável de controlo*/

	printf("Valor:%d\n", sem_valor_n(id, i));
}
