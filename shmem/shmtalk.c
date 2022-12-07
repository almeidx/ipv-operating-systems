#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0666 /* permissões para outros utilizadores */
#define MAXTEXTO 100

/*Organização da memória partilhada*/
struct s_shm {
	int pid_escritor;
	int id_msg;
	char texto[MAXTEXTO];
};

int main(int argc, char *argv[]) {
	int chave, id, pid, last_id_msg;
	struct s_shm *ptr; /*ponteiro para aceder ao segmento*/
	char aux[MAXTEXTO];

	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*Cria/Acede memória partilhada*/
	chave = atoi(argv[1]);
	id = shmget(chave, sizeof(struct s_shm), IPC_CREAT | PERMISSOES);
	exit_on_error(id, "Erro ao tentar criar/aceder a mem. partilhada\n");

	/* acoplamento */
	ptr = (struct s_shm *)shmat(id, NULL, 0);

	if (fork()) { /*Pai*/
		while (1) {
			fgets(aux, MAXTEXTO, stdin); /* newline incluído (se couber) */
			/* Secção crítica não tratada!!*/
			strcpy(ptr->texto, aux);
			ptr->pid_escritor = getpid();
			ptr->id_msg++;
		}
	} else { /*filho*/
		last_id_msg = 0;
		pid = getppid();
		while (1) {
			/* Secção crítica não tratada!!*/
			if ((ptr->pid_escritor != pid) && (last_id_msg < ptr->id_msg)) {
				last_id_msg = ptr->id_msg;
				printf("%d> %s", ptr->pid_escritor, ptr->texto);
			}
		}
	}

	shmdt(ptr); /* (nunca chega a ser executado) */
}
