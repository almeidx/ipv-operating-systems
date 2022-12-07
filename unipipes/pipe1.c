#include <stdio.h>
#include <unistd.h>

int main() {
	int fd[2], i, j;
	pipe(fd);		  /* Criação do pipe */
	if (!fork()) {	  /* filho envia, pai recebe*/
		close(fd[0]); /* este processo não usa lado de leitura */
		for (i = 0; i < 10; i++)
			write(fd[1], &i, sizeof(int));
		close(fd[1]);
	} else {
		close(fd[1]); /* este processo não usa lado de escrita */
		for (i = 0; i < 10; i++) {
			read(fd[0], &j, sizeof(int));
			printf("%d\n", j);
		}
		close(fd[0]);
	}
}
