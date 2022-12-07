#include "sem_funcoes.h"
#include "semprodcons.h"

int main(int argc, char *argv[]) {
	int chave, idshm, idsem, i;
	struct s_shm *ptr; /*ponteiro para aceder ao segmento*/
	struct s_item item;

	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*id memória partilhada*/
	chave = atoi(argv[1]);

	idshm = shmget(chave, 0, 0);
	exit_on_error(idshm, "Erro ao tentar aceder a mem. partilhada\n");

	/*id semáforos*/
	idsem = sem_id(chave);

	/* acoplamento */
	ptr = (struct s_shm *)shmat(idshm, NULL, 0);

	/* Consumidor */
	for (i = 0; i < MAXITENS; i++) {
		sem_operacao_n(idsem, SEM_CHEIO, -1); /*espera SEM_CHEIO*/
		sem_operacao_n(idsem, SEM_MUTEX, -1); /*espera SEM_MUTEX*/

		/*Consome item*/
		item = ptr->itens[ptr->out];

		printf("Consumidor: item %d %s\n", item.id, item.texto);

		ptr->out = (ptr->out + 1) % BUFFER;
		sem_operacao_n(idsem, SEM_MUTEX, +1); /*assinala SEM_MUTEX*/
		sem_operacao_n(idsem, SEM_VAZIO, +1); /*assinala SEM_VAZIO*/

		sleep(1); /*Simula atividade*/
	}

	/* desacoplamento */
	shmdt(ptr); /* feito automaticamente quando o processo termina*/
}
