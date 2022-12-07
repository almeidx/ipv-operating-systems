#include "sem_funcoes.h"

int main(int argc, char *argv[]) {
	int chave, id, nsem, r, i;
	union semun su; /*definido em sem_funcoes.h*/
	struct semid_ds info_sem;

	/* Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	chave = atoi(argv[1]);
	id = sem_id(chave); /* Obtém id*/
	su.buf = &info_sem;

	r = semctl(id, 0, IPC_STAT, su);
	exit_on_error(r, "Erro a aceder ao semáforo");

	printf("Semáforo(s): chave=%d id=%d\n", chave, id);

	nsem = info_sem.sem_nsems;

	printf("N. de semáforos :%d\n", nsem);
	printf("UID: %d GID: %d Permissões: %o\n", info_sem.sem_perm.uid, info_sem.sem_perm.gid, info_sem.sem_perm.mode);

	for (i = 0; i < nsem; i++) {
		printf("S[%d] valor=%d\n", i, semctl(id, i, GETVAL));
		printf("S[%d] Proc. Bloq.=%d\n", i, semctl(id, i, GETNCNT));
		printf("S[%d] Proc. Bloq. Wait40=%d\n", i, semctl(id, i, GETZCNT));
	}
}
