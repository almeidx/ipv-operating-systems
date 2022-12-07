#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main() {
	int fd[2], i, n;
	char c = 'A';
	pipe(fd);
	/* testar a capacidade, escrevendo no pipe
	até que fica bloqueado*/
	i = 1;
	while (1) {
		n = write(fd[1], &c, sizeof(char));
		exit_on_error(n, "Erro:");
		printf("%d bytes escrito no pipe.\n", i++);
	}
}
