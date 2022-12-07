#include "sem_funcoes.h"
#include "semrdwr.h"

int aleatorio(int de, int ate) { return de + (int)(((double)(ate - de + 1)) * rand() / (RAND_MAX + 1.0)); }

int main(int argc, char *argv[]) {
	int chave, idshm, idsem, nwr, i, iwr;
	struct s_shm *ptr; /*ponteiro para aceder ao segmento*/

	/*Usage*/
	if (argc != 3) {
		printf("Usage: %s <chave> <no escritores>\n", argv[0]);
		exit(1);
	}

	/*Cria memória partilhada*/
	chave = atoi(argv[1]);

	idshm = shmget(chave, sizeof(struct s_shm), IPC_CREAT | PERMISSOES);
	exit_on_error(idshm, "Erro ao tentar criar/aceder a mem. partilhada\n");

	/*Cria e inicializa semaforos*/
	idsem = sem_criar_n(chave, 2, PERMISSOES);
	sem_ini_var_n(idsem, SEM_MUTEX, 1);
	sem_ini_var_n(idsem, SEM_ESCRITA, 1);

	/* acoplamento */
	ptr = (struct s_shm *)shmat(idshm, NULL, 0);

	/* inicialização de dados*/
	ptr->NLeitores = 0;

	sprintf(ptr->texto, "Vazio");

	nwr = atoi(argv[2]);

	/* cria escritores (-1) */
	for (i = 0; i < (nwr - 1); i++)
		if (fork() == 0)
			break;

	/*escritor i*/
	srand(getpid()); /*Inicializa gerador de numeros aleatorios*/

	iwr = 0;

	while (1) {
		sleep(aleatorio(1, 10)); /*simula outra actividade*/
		sem_operacao_n(idsem, SEM_ESCRITA, -1);

		/*escrita*/
		printf("Escritor %d\n", i);
		iwr++;

		sprintf(ptr->texto, "Escrito por escritor %d No op. escrita %d", i, iwr);

		sem_operacao_n(idsem, SEM_ESCRITA, +1);
	}
}
