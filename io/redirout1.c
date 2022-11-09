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

#define NOME_DO_FICH "saida1.txt"

int main() {
	int fd;

	printf("Esta mensagem vai para o stdout\n");

	fd = open(NOME_DO_FICH, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	exit_on_error(fd, "Erro na abertura/criacao do ficheiro");

	close(1); /* fecha-se o stdout*/
	/*Fica livre o indice 1 da tabela de descritores */

	dup(fd); /* stdout = fd = 'saida'*/
			 /*Usa o primeiro indice livre da tabela de descritores (=1)*/
			 /*Nota: dup2(fd,1);<=>close(1); dup(fd); */

	close(fd); /* pode ser encerrado !!*/
	execlp("ls", "ls", "-l", NULL);
}
