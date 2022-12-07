#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

/* Modulo de funções de semáforos */
/* Este modulo nao pretende conter todas as "combinações" possíveis;
apenas algumas das funções mais utilizadas nos exercícios estudados*/
union semun {			   /* código copiado da manpage da semctl: */
	int val;			   /* value for SETVAL */
	struct semid_ds *buf;  /* buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* array for GETALL, SETALL */
	/* Linux specific part: */
	struct seminfo *__buf; /* buffer for IPC_INFO */
};

int sem_criar_n(int chave, int numero_de_semaforos, int permissoes);
void sem_ini_var_n(int id, int indice_do_semaforo, int valor);
int sem_criar(int chave, int permissoes, int valor);
int sem_id(int chave);
void sem_remover(int id);
void sem_operacao_n(int id, int indice_do_semaforo, int operacao);
void sem_operacao(int id, int operacao);
int sem_valor_n(int id, int indice_do_semaforo);
int sem_valor(int id);
void sem_esperar(int id);
void sem_assinalar(int id);
void sem_wait40(int id);
