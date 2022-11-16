#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int n = 0;

void tocou_alarme(int sinal_recebido) { n++; }

int main() {
	struct sigaction sa = {0};
	sa.sa_handler = tocou_alarme;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;			   /* POSIX */
	/*sa.sa_flags=SA_RESETHAND;*/  /* BSD*/
	sigaction(SIGALRM, &sa, NULL); /* trata SIGALRM */
	printf("A iniciar uma espera não activa...\n");
	while (n < 3) {
		alarm(5); /*Envia sinal SIGALRM dentro de 5 s*/
		pause();  /*Espera pela recepção de um sinal*/
		printf("%dº alarme\n", n);
	}
	printf("Não há maneira de acordar!!\n");
}
