#include "chat.h"

int mygetline(char line[], int max) {
	int nch = 0, c;
	max = max - 1; /* espaço for '\0' */
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			break;
		if (nch < max) {
			line[nch] = c;
			nch = nch + 1;
		}
	}

	if (c == EOF && nch == 0)
		return EOF;

	line[nch] = '\0';

	return nch;
}

int main(int argc, char *argv[]) {
	int chave, id, r;
	long para;
	char *line = NULL;
	struct s_msg msg;
	if (argc != 3) {
		printf("Usage: %s <chave> <sala>\n", argv[0]);
		exit(1);
	}
	chave = atoi(argv[1]);
	id = msgget(chave, 0); /* Obtem id da fila*/
	exit_on_error(id, "Erro ao tentar abrir fila");
	if (fork()) {				  /* pai */
		msg.para = 1;			  /*destino = srvchat*/
		msg.de = getpid();		  /*remetente*/
		msg.sala = atoi(argv[2]); /*id sala*/
		/* ler do stdin e escreve na fila de mensagens */
		while (1) {
			r = mygetline(msg.texto, MAXMSG);
			r = msgsnd(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), 0);
			exit_on_error(r, "Erro no envio da mensagem para a fila\n");
		}
	} else { /*filho*/
		/* Aguarda mensagens na fila */
		para = getppid();
		while (1) {
			r = msgrcv(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), para, 0);
			exit_on_error(r, "Erro na leitura de mensagem");
			printf("%d> %s\n", msg.de, msg.texto);
		}
	}
}
