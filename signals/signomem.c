#define ESPERA 15

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int contador = 0;

void trataUSR1(int sinal) {
	printf("Recebi o sinal (%d) pela %dª vez\n", sinal, ++contador);
	sleep(ESPERA); /* aguarda algum tempo tratamento do sinal */
	printf("OK, estou pronto para outro...\n");
}

int main() {
	struct sigaction sa;
	sa.sa_handler = trataUSR1;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL); /*trata SIGUSR1*/
	printf("Estou preparado para tratar sinais SIGUSR1\n");
	printf("O tratamento demora pelo menos %d segundos\n", ESPERA);
	while (1)
		pause();
}
