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

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <ficheiro>\n", argv[0]);
		exit(1);
	}

	if (open(argv[1], O_RDWR) == -1) {
		perror("Erro na abertura do ficheiro");
		exit(1);
	} else {
		printf("OK\n");
	}

	return 0;
}
