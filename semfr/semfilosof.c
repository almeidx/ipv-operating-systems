#include "sem_funcoes.h"
#include <stdio.h>
#include <stdlib.h>

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define N 5				/*Numero de Filósofos*/
#define SEM_MUTEX N
#define ESQUERDA (i + N - 1) % N
#define DIREITA (i + 1) % N
#define PENSAR 0
#define FOME 1
#define COMER 2

/*Organização da memória partilhada*/
struct s_shm {
	int estado[N];
};

int aleatorio(int de, int ate) { return de + (int)(((double)(ate - de + 1)) * rand() / (RAND_MAX + 1.0)); }

struct s_shm *ptr; /*ponteiro para aceder ao segmento*/

int idsem; /*id semáforos*/

void teste(int i) {
	if (ptr->estado[i] == FOME && ptr->estado[ESQUERDA] != COMER && ptr->estado[DIREITA] != COMER) {
		ptr->estado[i] = COMER;
		sem_operacao_n(idsem, i, +1);
	} /* Assinala semáforo i*/
}

void ApanharPauzinhos(int i) {
	sem_operacao_n(idsem, SEM_MUTEX, -1); /*Espera MUTEX*/
	ptr->estado[i] = FOME;
	teste(i);
	sem_operacao_n(idsem, SEM_MUTEX, +1); /*Assinala MUTEX*/
	sem_operacao_n(idsem, i, -1);		  /*Espera semáforo i*/
}

void PousarPauzinhos(int i) {
	sem_operacao_n(idsem, SEM_MUTEX, -1); /*Espera MUTEX*/
	ptr->estado[i] = PENSAR;
	teste(ESQUERDA);
	teste(DIREITA);
	sem_operacao_n(idsem, SEM_MUTEX, +1); /*Assinala MUTEX*/
}

int main() {
	int idshm, i, nc;

	/*Cria memória partilhada*/
	idshm = shmget(IPC_PRIVATE, sizeof(struct s_shm), IPC_CREAT | PERMISSOES);
	exit_on_error(idshm, "Erro ao tentar criar/aceder a mem. partilhada\n");

	/*Cria e inicializa semaforos*/
	idsem = sem_criar_n(IPC_PRIVATE, N + 1, PERMISSOES);
	sem_ini_var_n(idsem, SEM_MUTEX, 1);

	for (i = 0; i < N; i++)
		sem_ini_var_n(idsem, i, 0);

	/* acoplamento */
	ptr = (struct s_shm *)shmat(idshm, NULL, 0);

	/* inicialização de dados*/
	for (i = 0; i < N; i++)
		ptr->estado[i] = PENSAR;

	/* cria proc. filosofos */
	for (i = 0; i < (N - 1); i++)
		if (fork() == 0)
			break;

	/*Filosofo i*/
	nc = 0;
	srand(getpid()); /*Inicializa gerador de números aleatórios*/

	while (1) {
		printf("Filosofo %d a pensar\n", i);
		sleep(aleatorio(1, 3));
		ApanharPauzinhos(i);
		nc++;
		printf("Filosofo %d a comer pela %d-ésima vez\n", i, nc);
		sleep(aleatorio(1, 3));
		PousarPauzinhos(i);
	}
}
