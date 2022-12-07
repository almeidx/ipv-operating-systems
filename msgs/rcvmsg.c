#include "defmsg.h"

int main(int argc, char *argv[]) {
	int r, chave, id;
	long tipo;
	struct s_msg msg; /*Estrutura da mensagem*/
	/*Usage*/
	if (argc != 3) {
		printf("Usage: %s <chave> <tipo>\n", argv[0]);
		exit(1);
	}
	chave = atoi(argv[1]);
	id = msgget(chave, 0); /*Obter id*/
	exit_on_error(id, "Erro ao tentar obter o id da fila\n");
	/*Aguarda mensagem*/
	tipo = atol(argv[2]);
	printf("Aguarda mensagem do tipo=%ld\n", tipo);
	r = msgrcv(id, (struct msgbuf *)&msg, sizeof(msg) - sizeof(long), tipo, 0);
	exit_on_error(r, "Erro ao ler mensagem da fila\n");
	printf("Mensagem recebida: tipo=%ld texto=%s\n", msg.tipo, msg.texto);
}
