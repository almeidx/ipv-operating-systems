#include "sem_funcoes.h"
#include <stdio.h>

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define N 5				/*Numero de Cadeiras*/
#define N_CLIENTES 10	/*Numero de Clientes*/
#define SEM_MUTEX 0
#define SEM_CADEIRA 1
#define SEM_BARBEIRO 2

int aleatorio(int de, int ate) { return de + (int)(((double)(ate - de + 1)) * rand() / (RAND_MAX + 1.0)); }

int *clientes;
int idsem; /*id semáforos*/

void TarefaCliente(int i) {
	sem_operacao_n(idsem, SEM_MUTEX, -1); /*Espera MUTEX*/
	if (*clientes < N) {
		*clientes = *clientes + 1;
		printf("Cliente %d: cliente à espera\n", i);
		sem_operacao_n(idsem, SEM_BARBEIRO, +1); /*Assinala BARBEIRO*/
		sem_operacao_n(idsem, SEM_MUTEX, +1);	 /*Assinala MUTEX*/
		sem_operacao_n(idsem, SEM_CADEIRA, -1);	 /*Espera Cadeira*/
		printf("Cliente %d: a sentar na cadeira\n", i);
	} else {
		printf("Cliente %d: volta mais tarde\n", i);
		sem_operacao_n(idsem, SEM_MUTEX, +1);
	} /*Assinala MUTEX*/
}

void TarefaBarbeiro() {
	sem_operacao_n(idsem, SEM_BARBEIRO, -1); /*Espera BARBEIRO*/
	sem_operacao_n(idsem, SEM_MUTEX, -1);	 /*Espera MUTEX*/
	printf("Barbeiro:No de clientes sentados à espera=%d\n", *clientes);
	*clientes = *clientes - 1;
	sem_operacao_n(idsem, SEM_MUTEX, +1);	/*Assinala MUTEX*/
	sem_operacao_n(idsem, SEM_CADEIRA, +1); /*Assinala CADEIRA*/
	printf("Barbeiro:a cortar cabelo\n");
	sleep(aleatorio(1, 2));
	printf("Barbeiro:+1 cliente satisfeito\n");
}

int main() {
	int idshm, i, pid;

	/*Cria memória partilhada*/
	idshm = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | PERMISSOES);
	exit_on_error(idshm, "Erro ao tentar criar/aceder a mem. partilhada\n");

	/*Cria e inicializa semaforos*/
	idsem = sem_criar_n(IPC_PRIVATE, 3, PERMISSOES);
	sem_ini_var_n(idsem, SEM_MUTEX, 1);
	sem_ini_var_n(idsem, SEM_CADEIRA, 0);
	sem_ini_var_n(idsem, SEM_BARBEIRO, 0);

	/* acoplamento */
	clientes = (int *)shmat(idshm, NULL, 0);

	/* inicialização de dados*/
	*clientes = 0;

	/* cria proc. clientes */
	pid = getpid();

	for (i = 0; i < (N_CLIENTES); i++)
		if (fork() == 0)
			break;

	srand(getpid()); /*Inicializa gerador de números aleatórios*/

	if (getpid() == pid) { /*Proc. Pai*/
		while (1) {
			TarefaBarbeiro();
		}
	} else { /*Proc. filho = Clientes*/
		/*Cliente i*/
		while (1) {
			sleep(aleatorio(5, 10));
			TarefaCliente(i);
		}
	}
}
