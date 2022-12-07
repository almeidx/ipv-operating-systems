#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}
#define NOME_FIFO "FIFO1"

int main() {
	int i, f;
	char c;
	f = mknod(NOME_FIFO, S_IFIFO | 0644, 0); /*ou mkfifo(NOME_DO_FIFO, 0644);*/
	exit_on_error(f, "Erro ao criar o fifo");
	printf("Bloqueado à espera que algum processo abra o fifo %s para leitura\n", NOME_FIFO);
	f = open(NOME_FIFO, O_WRONLY);
	exit_on_error(f, "Erro ao abrir o fifo");
	printf("OK! Alguém abriu o fifo para leitura. Já posso escrever!!\n");
	for (c = 'A'; c <= 'Z'; c++) {	/* escreve o alfabeto */
		write(f, &c, sizeof(char)); /*escrita no fifo*/
		sleep(1);
	}
}
