// #define _GNU_SOURCE
// #define _BSD_SOURCE
#define _POSIX_SOURCE

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int n = 0;

void tocou_alarme(int sinal_recebido) { n++; }

int main() {
	signal(SIGALRM, tocou_alarme); /* trata SIGALRM */
	printf("A iniciar uma espera não ativa...\n");

	while (n < 3) {
		alarm(5); /*Envia sinal SIGALRM dentro de 5 s*/
		pause();  /*Espera pela receção de um sinal*/
		printf("Alarme:%d\n", n);
	}

	printf("Não há maneira de acordar!!\n");

	return 0;
}
