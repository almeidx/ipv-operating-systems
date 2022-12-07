#include "chat.h"

int main(int argc, char *argv[]) {
	int chave, id, r, i, j;
	long para;
	struct s_msg msg;

	if (argc != 2) {
		printf("Usage: %s <chave>\n", argv[0]);
		exit(1);
	}

	/*Cria fila*/
	chave = atoi(argv[1]);
	id = msgget(chave, IPC_CREAT | IPC_EXCL | PERMISSOES);

	exit_on_error(id, "Erro ao tentar criar a fila");

	/*Inicializa estrutura de dados*/
	for (i = 0; i < MAXSALA; i++)
		for (j = 0; j < MAXPROC; j++)
			tsala[i][j] = 0; /*nenhum util. registado*/

	while (1) {
		/*Aguarda mensagens na fila */
		para = 1; /* servidor = 1*/
		r = msgrcv(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), para, 0);
		exit_on_error(r, "Erro na leitura de mensagem");
		printf("pid=%d sala=%d %s\n", msg.de, msg.sala, msg.texto);
		if (msg.sala < MAXSALA) {
			i = -1;
			for (j = 0; j < MAXPROC; j++)
				if (tsala[msg.sala][j] == 0) {
					if (i == -1)
						i = j;
				} else {
					if (tsala[msg.sala][j] != msg.de) { /*difunde pelos util. registados na sala*/
						msg.para = tsala[msg.sala][j];
						r = msgsnd(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), 0);
						exit_on_error(r, "Erro no envio de mensagem");
					} else {
						i = -2;
					} /*já registado na sala*/
				}

			if (i >= 0)
				tsala[msg.sala][i] = msg.de; /*regista na sala*/
		}
	}
}
