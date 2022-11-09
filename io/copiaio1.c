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

#define TAMANHO_DO_BUFFER 10

int main(int argc, char *argv[]) {
	char buffer[TAMANHO_DO_BUFFER];
	int n, fd_r, fd_w;

	if (argc == 2) {
		fd_r = open(argv[1], O_RDONLY);
		exit_on_error(fd_r, "Erro na abertura da origem");
		fd_w = STDIN_FILENO;
	} else if (argc == 3) {
		fd_r = open(argv[1], O_RDONLY);
		exit_on_error(fd_r, "Erro na abertura da origem");
		fd_w = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		exit_on_error(fd_r, "Erro na abertura/criação do destino");
	} else {
		fd_r = STDIN_FILENO;
		fd_w = STDOUT_FILENO;
	}

	while ((n = read(fd_r, buffer, TAMANHO_DO_BUFFER)) > 0)
		write(fd_w, buffer, n);

	return 0;
}
