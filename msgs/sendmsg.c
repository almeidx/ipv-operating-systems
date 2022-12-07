#include "defmsg.h"

int main(int argc, char *argv[]) {
	int r, chave, id;
	struct s_msg msg; /*Estrutura da mensagem*/
	/*Usage*/
	if (argc != 4) {
		printf("Usage: %s <chave> <tipo> <texto>\n", argv[0]);
		exit(1);
	}
	chave = atoi(argv[1]);
	id = msgget(chave, 0); /*Obter id*/
	exit_on_error(id, "Erro ao tentar obter o id da fila\n");
	/*Prepara mensagem*/
	msg.tipo = atol(argv[2]);
	strcpy(msg.texto, argv[3]);
	/*Envia mensagem*/
	r = msgsnd(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), 0);
	exit_on_error(r, "Erro ao enviar mensagem para a fila\n");
	printf("Mensagem enviada para:chave=%d id=%d\n", chave, id);
}
