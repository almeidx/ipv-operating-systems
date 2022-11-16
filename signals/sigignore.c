#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL); /* ignora SIGUSR1 */
	/* ou apenas signal(SIGUSR1, SIG_IGN); */
	printf("Vou ignorar os sinais SIGUSR1...\n");
	pause();
}
