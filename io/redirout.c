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

#define NOME_DO_FICH "saida.txt"

int main() {
	int fd;

	printf("Esta mensagem vai para o stdout\n");

	close(1); /* fecha-se o stdout*/

	/*Fica livre o índice 1 da tabela de descritores*/
	fd = open(NOME_DO_FICH, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	exit_on_error(fd, "Erro na abertura/criação do ficheiro");

	/*Usa o primeiro índice livre da tabela de descritores (=1)*/
	printf("Esta mensagem vai para o descritor %d = ficheiro, em vez do monitor\n", fd);

	close(fd);

	return 0;
}
