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

int main() {
	int i, pedido, resposta;
	/*Elimina no caso de existir*/
	unlink("PEDIDO");
	unlink("RESPOSTA");
	/*Cria FIFO*/
	i = mkfifo("PEDIDO", 0666);
	exit_on_error(i, "Erro a criar o FIFO:PEDIDO");
	i = mkfifo("RESPOSTA", 0666);
	exit_on_error(i, "Erro a criar o FIFO:RESPOSTA");
	/*Abre FIFO*/
	pedido = open("PEDIDO", O_RDONLY);
	exit_on_error(pedido, "Abertura do FIFO:pedido");
	resposta = open("RESPOSTA", O_WRONLY);
	exit_on_error(resposta, "Abertura do FIFO:pedido");
	while (read(pedido, &i, sizeof(int)) > 0) /*Leitura do FIFO*/
	{
		i = i * 2;
		write(resposta, &i, sizeof(int));
	} /*Escrita no FIFO*/
	close(pedido);
	unlink("PEDIDO");
	/* O FIFO resposta deve ser eliminado pelo processo clientf*/
}
