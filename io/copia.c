#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define TAMANHO_DO_BUFFER 10

int main(int argc, char *argv[]) {
	int n, fd_r, fd_w;
	char buffer[TAMANHO_DO_BUFFER];

	if (argc != 3) {
		printf("Usage: %s <de> <para>\n", argv[0]);
		exit(1);
	}

	fd_r = open(argv[1], O_RDONLY);
	exit_on_error(fd_r, "Erro na abertura da origem");

	fd_w = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	exit_on_error(fd_w, "Erro na abertura/criação do destino");

	/*Leitura de fd_r para fd_w*/
	while ((n = read(fd_r, buffer, TAMANHO_DO_BUFFER)) > 0)
		write(fd_w, buffer, n);

	exit_on_error(n, "Erro durante a leitura do ficheiro de origem");

	close(fd_r);
	close(fd_w);

	return 0;
}
