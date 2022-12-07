#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main() {
	int i, n, pedido, resposta;
	/*É suposto o servidor já estar a correr e ter criado os FIFO*/
	pedido = open("PEDIDO", O_WRONLY);
	exit_on_error(pedido, "Abertura do FIFO:pedido");
	resposta = open("RESPOSTA", O_RDONLY);
	exit_on_error(resposta, "Abertura do FIFO:pedido");
	printf("n?");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		write(pedido, &i, sizeof(int));			/*Escreve no FIFO*/
	close(pedido);								/*Essencial*/
	while (read(resposta, &i, sizeof(int)) > 0) /*Leitura do pipe*/
		printf("%d\n", i);
	close(resposta);
	unlink("RESPOSTA");
	/* O FIFO pedido deve ser eliminado pelo processo serverf*/
}
