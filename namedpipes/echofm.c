#include <fcntl.h>
#include <signal.h>
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
#define n_fifo "echofifo"

void trataSIGINT(int sinal) {}

int main() {
	int i, f;
	char c;
	struct sigaction sa;
	sa.sa_handler = trataSIGINT;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;			  /* POSIX */
	sigaction(SIGINT, &sa, NULL); /* trata SIGINT*/
	printf("Envie-me o sinal SIGINT para terminar. PID=%d\n", getpid());
	/*Elimina no caso de existir*/
	unlink(n_fifo);
	/*Cria FIFO*/
	i = mkfifo(n_fifo, 0666);
	exit_on_error(i, "Erro a criar o FIFO");
	/*Abre FIFO*/
	f = open(n_fifo, O_RDWR);
	exit_on_error(f, "Abertura do FIFO");
	printf("Podem escrever para FIFO:%s\n", n_fifo);
	while (read(f, &c, sizeof(char)) > 0)
		printf("%c", c);
	printf("Eliminação do FIFO\n");
	unlink(n_fifo);
}
