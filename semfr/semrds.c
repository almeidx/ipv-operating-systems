#include "sem_funcoes.h"
#include "semrdwr.h"

int aleatorio(int de, int ate) { return de + (int)(((double)(ate - de + 1)) * rand() / (RAND_MAX + 1.0)); }

int main(int argc, char *argv[]) {
	int chave, idshm, idsem, nrd, i;
	struct s_shm *ptr; /*ponteiro para aceder ao segmento*/

	/*Usage*/
	if (argc != 3) {
		printf("Usage: %s <chave> <no leitores>\n", argv[0]);
		exit(1);
	}

	/*Acede a memória partilhada*/
	chave = atoi(argv[1]);

	idshm = shmget(chave, 0, 0);
	exit_on_error(idshm, "Erro ao tentar aceder a mem. partilhada\n");

	/*Obtém id do semaforos*/
	idsem = sem_id(chave);

	/* acoplamento */
	ptr = (struct s_shm *)shmat(idshm, NULL, 0);

	nrd = atoi(argv[2]);

	/* cria escritores (-1) */
	for (i = 0; i < (nrd - 1); i++)
		if (fork() == 0)
			break;

	/*leitor i*/
	srand(getpid()); /*Inicializa gerador de números aleatórios*/

	while (1) {
		sleep(aleatorio(1, 10));			  /*simula outra atividade*/
		sem_operacao_n(idsem, SEM_MUTEX, -1); /*Espera MUTEX*/
		ptr->NLeitores++;

		if (ptr->NLeitores == 1)
			sem_operacao_n(idsem, SEM_ESCRITA, -1); /*Espera ESCRITA*/

		sem_operacao_n(idsem, SEM_MUTEX, +1); /*Assinala MUTEX*/

		/*leitura*/
		printf("Leitor %d texto lido:%s\n", i, ptr->texto);

		sleep(aleatorio(1, 2)); /*Simula tempo de leitura*/

		sem_operacao_n(idsem, SEM_MUTEX, -1); /*Espera MUTEX*/

		ptr->NLeitores--;

		if (ptr->NLeitores == 0)
			sem_operacao_n(idsem, SEM_ESCRITA, +1); /*Assinala ESCRITA*/

		sem_operacao_n(idsem, SEM_MUTEX, +1); /*Assinala MUTEX*/
	}
}
