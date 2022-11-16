#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void trataTodos(int sinal) { printf("Recebi o sinal %d\n", sinal); }

int main() {
	int i;
	struct sigaction sa;
	sa.sa_handler = trataTodos;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	for (i = 1; i <= 31; i++)
		sigaction(i, &sa, NULL); /*trata sinal i*/
	printf("Estou preparado para tratar todos (quase) os sinais\n");
	while (1)
		pause();
}
