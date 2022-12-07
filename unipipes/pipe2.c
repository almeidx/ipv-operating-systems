#include <stdio.h>
#include <unistd.h>

int main() {
	int fd[2], i, n;
	pipe(fd); /* Criação do pipe */

	if (!fork()) { /* filho envia, pai recebe */
		printf("n?");
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			write(fd[1], &i, sizeof(int));
	} else {
		close(fd[1]);							 /*ESSENCIAL!!!*/
		while (read(fd[0], &i, sizeof(int)) > 0) /* + dados? */
			printf("%d\n", i);
	}
}
