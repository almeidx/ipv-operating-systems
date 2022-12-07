#include "sem_funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PERMISSOES 0600

int main() {
	int chave, idping, idpong, *i;

	/*Cria semáforos*/
	idping = sem_criar(IPC_PRIVATE, PERMISSOES, 1);
	idpong = sem_criar(IPC_PRIVATE, PERMISSOES, 0);

	if (fork()) { /*Pai*/
		while (1) {
			sem_operacao(idping, -1); /* esperar*/
			printf("Ping!\n");
			sleep(1);
			sem_operacao(idpong, 1); /* assinalar "autoriza"*/
		}
	} else { /*Filho*/
		while (1) {
			sem_operacao(idpong, -1); /* esperar*/
			printf("Pong!\n");
			sleep(2);
			sem_operacao(idping, 1); /*assinalar "autoriza"*/
		}
	}
}
