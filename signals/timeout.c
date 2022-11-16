#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void timeout(int sinal) { printf("Alarme\n"); }

int main() {
	int n;
	char s[10];
	struct sigaction sa;
	sa.sa_handler = timeout;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;			/* POSIX */
	/*sa.sa_flags=SA_RESTART;*/ /* BSD */
	printf("Bloqueado em read() à espera de E/S...\n");
	sigaction(SIGALRM, &sa, NULL); /* trata SIGALRM */
	alarm(10);					   /*Envia sinal SIGALRM dentro de 10 s*/
	n = read(0, s, 10);			   /* n=scanf("%9[^\n]",s); */
	if (n == -1) {
		if (errno == EINTR)
			printf("Terminou o tempo!!\n");
		else
			perror("Erro:");
	} else
		printf("s=%s\n", s);
}
