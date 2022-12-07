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

	/*Cria memória partilhada*/
	chave = atoi(argv[1]);
	id = shmget(chave, sizeof(struct s_shm), IPC_CREAT | PERMISSOES);
	exit_on_error(id, "Erro ao tentar criar/aceder a mem. partilhada\n");

	/* acoplamento */
	ptr = (struct s_shm *)shmat(id, NULL, 0);

	/* inicialização de dados*/
	ptr->in = 0;
	ptr->out = 0;
	ptr->counter = 0;

	/* produtor */
	for (i = 0; i < MAXITENS; i++) {
		/*Esta secção deverá ser corrigida para garantir a
		correta sincronização entre produtor e consumidor (semáforos)*/
		while (ptr->counter == BUFFER)
			; /*Espera ativa */

		/*Produz item*/
		sprintf(item.texto, "Item %d", i);
		item.id = i;

		ptr->itens[ptr->in] = item; /* Guarda no buffer*/
		printf("Produtor: %d %s\n", ptr->itens[ptr->in].id, ptr->itens[ptr->in].texto);

		ptr->in = (ptr->in + 1) % BUFFER;

		/*Incrementa contador*/
		ptr->counter++;
	}

	/* desacoplamento */
	shmdt(ptr); /* feito automaticamente quando o processo termina*/
}
