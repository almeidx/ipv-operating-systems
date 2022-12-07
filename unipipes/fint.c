#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int i, j, fd_w;
	if (argc <= 2) {
		printf("Usage: %s <fich> <i1> <i2> ... <in>\n", argv[0]);
		exit(1);
	}
	if ((fd_w = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1) {
		perror("Erro na abertura/criação do ficheiro de destino");
		exit(1);
	}
	for (i = 2; i < argc; i++) {
		j = atoi(argv[i]);
		write(fd_w, &j, sizeof(int));
	}
	close(fd_w);
}
