#include "shmprodcons.h"

int main(int argc, char *argv[]) {
	int chave, id, i;
	struct s_shm *ptr; /*ponteiro para aceder ao segmento*/
	struct s_item item;

	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*Acede à memória partilhada*/
	chave = atoi(argv[1]);
	id = shmget(chave, 0, 0);
	exit_on_error(id, "Erro ao tentar aceder a mem. partilhada\n");

	/* acoplamento */
	ptr = (struct s_shm *)shmat(id, NULL, 0);

	/* Consumidor */
	for (i = 0; i < MAXITENS; i++) {
		/*Esta secção deverá ser corrigida para garantir a
		correta sincronização entre produtor e consumidor (semáforos)*/
		while (ptr->counter == 0)
			; /*Espera ativa*/

		/*Consome item*/
		item = ptr->itens[ptr->out];
		printf("Consumidor: item %d %s\n", item.id, item.texto);

		ptr->out = (ptr->out + 1) % BUFFER;

		/*Decrementa contador*/
		ptr->counter--;

		sleep(1); /*Simula actividade*/
	}

	/* desacoplamento */
	shmdt(ptr); /* feito automaticamente quando o processo termina*/
}
