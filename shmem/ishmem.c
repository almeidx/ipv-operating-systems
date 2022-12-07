#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}
#define PERMISSOES 0600 /* admita-se que serve para o exemplo */

int main(int argc, char *argv[]) {
	struct shmid_ds info_shm;
	int chave, id, r;

	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*Acede à mem. partilhada*/
	chave = atoi(argv[1]);
	id = shmget(chave, 0, 0); /* Obtém id */
	exit_on_error(id, "Erro ao tentar aceder ao segmento\n");

	/*Obtém info do segmento*/
	r = shmctl(id, IPC_STAT, &info_shm);
	exit_on_error(r, "Erro ao tentar aceder ao segmento\n");

	printf("Id do segmento :%d\n", id);
	printf("Id do proprietário :%d\n", info_shm.shm_perm.uid);
	printf("Id do grupo do proprietário:%d\n", info_shm.shm_perm.gid);
	printf("Id do criador :%d\n", info_shm.shm_perm.cuid);
	printf("Id do grupo do criador :%d\n", info_shm.shm_perm.cgid);
	printf("Permissões de acesso :%o\n", info_shm.shm_perm.mode);
	printf("N. de bytes do segmento :%ld\n", info_shm.shm_segsz);
	printf("PID do último acesso :%d\n", info_shm.shm_lpid);
	printf("Data do último attach :%s\n", ctime(&info_shm.shm_atime));
	printf("Data do último detach :%s\n", ctime(&info_shm.shm_dtime));
	printf("N. de processos acoplados :%ld\n", info_shm.shm_nattch);
}
