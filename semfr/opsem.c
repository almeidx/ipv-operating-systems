#include "sem_funcoes.h"

int main(int argc, char *argv[]) {
	int chave, id, i, op;

	/* Usage*/
	if (argc != 4) {
		printf("Usage: %s <chave> <índice> <operação>\n", argv[0]);
		exit(1);
	}

	chave = atoi(argv[1]);
	i = atoi(argv[2]);
	op = atoi(argv[3]);

	id = sem_id(chave); /* Obtém id */

	printf("Semáforo: chave=%d id=%d índice=%d\n", chave, id, i);
	printf("Valor :%d\n", sem_valor_n(id, i));
	printf("Tenta operação: %d\n", op);

	sem_operacao_n(id, i, op);

	printf("Operação realizada/Proc. desbloqueado\n");
	printf("Valor :%d\n", sem_valor_n(id, i));
}
