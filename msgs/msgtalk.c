#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}
#define PERMISSOES 0666 /* permissões para outros utilizadores */
#define TAMANHO 100		/* assumir que chega */

struct s_msg {
	long para; /* 1º campo: long obrigatório = PID destinatário*/
	long de;   /* PID remetente*/
	char texto[TAMANHO];
};

int main(int argc, char *argv[]) {
	int chave, id, r;
	long para;
	struct s_msg msg;
	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}
	chave = atoi(argv[1]);
	/* o primeiro a tentar aceder à fila cria-a*/
	id = msgget(chave, IPC_CREAT | PERMISSOES);
	exit_on_error(id, "Erro ao tentar criar/abrir fila de mensagens");
	printf("Enviem mensagens do tipo PID=%d\n", getpid());
	if (fork()) { /* pai */
		/* ler do stdin e escreve na fila de mensagens */
		msg.de = getpid();
		while (1) {
			scanf(" %ld %[^\n]s", &msg.para, msg.texto);
			r = msgsnd(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), 0);
			exit_on_error(r, "Erro no envio da mensagem para a fila\n");
		}
	} else { /*filho*/
		/* Aguarda mensagens na fila */
		para = getppid();
		while (1) {
			r = msgrcv(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), para, 0);
			exit_on_error(r, "Erro na leitura de mensagem");
			printf("%ld> %s\n", msg.de, msg.texto);
		}
	}
}
