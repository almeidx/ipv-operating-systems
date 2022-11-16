#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ping(int sinal) { printf("Ping\n"); }
void pong(int sinal) { printf("Pong\n"); }

int main() {
	int fid;
	fid = fork();
	if (fid) /* Pai = Pong */
	{
		signal(SIGUSR1, pong); /*trata sinal SIGUSR1*/
		while (1) {
			sleep(1);
			kill(fid, SIGUSR1); /*envia sinal ao filho*/
			pause();			/*aguarda sinal*/
		}
	} else /* Filho = Ping */
	{
		signal(SIGUSR1, ping); /*trata sinal SIGUSR1*/
		while (1) {
			pause(); /*aguarda sinal*/
			sleep(1);
			kill(getppid(), SIGUSR1);
		} /*envia sinal ao pai*/
	}
}
