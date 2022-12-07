#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main(int argc, char *argv[]) {
	struct msqid_ds info_msg;
	int chave, id, r;
	/*Usage*/
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}
	/*Acede à fila de mensagens*/
	chave = atoi(argv[1]);
	id = msgget(chave, 0); /* Obtém id */
	exit_on_error(id, "Erro ao tentar obter id a fila\n");
	/*Obtém info da fila*/
	r = msgctl(id, IPC_STAT, &info_msg);
	exit_on_error(r, "Erro ao tentar aceder a fila\n");
	printf("Id da fila de mensagens :%d\n", id);
	printf("Id do proprietário :%d\n", info_msg.msg_perm.uid);
	printf("Id do grupo do proprietário:%d\n", info_msg.msg_perm.gid);
	printf("Id do criador :%d\n", info_msg.msg_perm.cuid);
	printf("Id do grupo do criador :%d\n", info_msg.msg_perm.cgid);
	printf("Permissões de acesso :%o\n", info_msg.msg_perm.mode);
	printf("N. actual de bytes na fila :%ld\n", info_msg.msg_cbytes);
	printf("N. de mensagens na fila :%ld\n", info_msg.msg_qnum);
	printf("N. máximo de bytes na fila :%ld\n", info_msg.msg_qbytes);
	printf("PID do ultimo escritor :%d\n", info_msg.msg_lspid);
	printf("PID do ultimo leitor :%d\n", info_msg.msg_lrpid);
	printf("Data da ultima escrita :%s", ctime(&info_msg.msg_stime));
	printf("Data da ultima leitura :%s", ctime(&info_msg.msg_rtime));
	printf("Data da ultima modificação :%s", ctime(&info_msg.msg_ctime));
}
