#include "defshm.h"

int main(int argc, char *argv[]) {
	int chave, id, i;
	struct s_shm *ptr; /*ponteiro para aceder ao segmento*/

	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*Cria memória partilhada*/
	chave = atoi(argv[1]);
	id = shmget(chave, 0, 0); /*Obtem id*/
	exit_on_error(id, "Erro ao tentar aceder a mem. partilhada\n");

	/* acoplamento */
	ptr = (struct s_shm *)shmat(id, NULL, 0);

	/* leitura da memória */
	for (i = 0; i < TAMANHO; i++)
		printf("%d ", ptr->tabela[i]);

	printf("\n");

	/* desacoplamento */
	shmdt(ptr); /* feito automaticamente quando o processo termina*/
}
