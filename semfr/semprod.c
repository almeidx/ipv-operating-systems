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

	/*Cria memória partilhada*/
	chave = atoi(argv[1]);

	idshm = shmget(chave, sizeof(struct s_shm), IPC_CREAT | PERMISSOES);
	exit_on_error(idshm, "Erro ao tentar criar/aceder a mem. partilhada\n");

	/*Cria e inicializa semaforos*/
	idsem = sem_criar_n(chave, 3, PERMISSOES);
	sem_ini_var_n(idsem, SEM_MUTEX, 1);
	sem_ini_var_n(idsem, SEM_VAZIO, BUFFER);
	sem_ini_var_n(idsem, SEM_CHEIO, 0);

	/* acoplamento */
	ptr = (struct s_shm *)shmat(idshm, NULL, 0);

	/* inicialização de dados*/
	ptr->in = 0;
	ptr->out = 0;

	/* produtor */
	for (i = 0; i < MAXITENS; i++) {
		sem_operacao_n(idsem, SEM_VAZIO, -1); /*espera SEM_VAZIO*/
		sem_operacao_n(idsem, SEM_MUTEX, -1); /*espera SEM_MUTEX*/

		/*Produz item*/
		sprintf(item.texto, "Item %d", i);

		item.id = i;
		ptr->itens[ptr->in] = item; /* Guarda no buffer*/

		printf("Produtor: %d %s\n", ptr->itens[ptr->in].id, ptr->itens[ptr->in].texto);

		ptr->in = (ptr->in + 1) % BUFFER;

		sem_operacao_n(idsem, SEM_MUTEX, +1); /*assinala SEM_MUTEX*/
		sem_operacao_n(idsem, SEM_CHEIO, +1); /*assinala SEM_CHEIO*/
	}

	/* desacoplamento */
	shmdt(ptr); /* feito automaticamente quando o processo termina*/
}
