#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int i;
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	for (i = 1; i <= 31; i++)
		sigaction(i, &sa, NULL); /* ignora sinal i */
	/* ou apenas signal(i, SIG_IGN); */
	printf("Vou tentar ignorar todos os sinais..\n");
	pause();
}
