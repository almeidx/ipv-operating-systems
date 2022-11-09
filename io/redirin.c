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
	char buffer[100];

	close(0); /* fecha-se o stdin*/

	/*Fica livre o índice 0 da tabela de descritores*/
	fd = open(NOME_DO_FICH, O_RDONLY);
	exit_on_error(fd, "Erro na abertura do ficheiro");

	/*Usa o primeiro índice da tabela de descritores (=0)*/
	scanf("%[^\n]", buffer); /*Leitura do descritor 0*/

	printf("Foi lido: \"%s\"\n", buffer);

	close(fd);

	return 0;
}
