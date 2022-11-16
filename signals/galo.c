#define ADVERSARIO 10
#define JOGADOR 1
#define VAZIO 0

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int sinais[9] = {SIGHUP, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGBUS, SIGFPE, SIGUSR1, SIGUSR2};
int jogo[9] = {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO};

void trataSinal(int sinal) {
	int i;
	for (i = 0; i < 9; i++)
		if (sinais[i] == sinal)
			jogo[i] = ADVERSARIO;
}

void mostraJogo() {
	int i;
	char ch;
	for (i = 0; i < 9; i++) {
		if (i % 3 == 0)
			printf("-------\n");
		if (jogo[i] == VAZIO)
			ch = ' ';
		if (jogo[i] == ADVERSARIO)
			ch = '0';
		if (jogo[i] == JOGADOR)
			ch = 'X';
		printf("|%c", ch);
		if (i % 3 == 2)
			printf("|\n");
	}
	printf("-------\n");
}

void jogada(int pid) {
	int i = -1;
	while (!((i >= 0) && (i <= 8))) {
		printf("Jogada (0..8)?");
		scanf("%d", &i);
	}
	jogo[i] = JOGADOR;
	if (kill(pid, sinais[i]) == -1) {
		perror("Erro:");
		exit(1);
	}
}

int terminou() {
	int i;
	if (jogo[0] + jogo[1] + jogo[2] == 3 || jogo[3] + jogo[4] + jogo[5] == 3 || jogo[6] + jogo[7] + jogo[8] == 3 ||
		jogo[0] + jogo[3] + jogo[6] == 3 || jogo[1] + jogo[4] + jogo[7] == 3 || jogo[2] + jogo[5] + jogo[8] == 3 ||
		jogo[0] + jogo[4] + jogo[8] == 3 || jogo[2] + jogo[4] + jogo[6] == 3) {
		printf("Ganhei :-)\n");
		return 1;
	}
	if (jogo[0] + jogo[1] + jogo[2] == 30 || jogo[3] + jogo[4] + jogo[5] == 30 || jogo[6] + jogo[7] + jogo[8] == 30 ||
		jogo[0] + jogo[3] + jogo[6] == 30 || jogo[1] + jogo[4] + jogo[7] == 30 || jogo[2] + jogo[5] + jogo[8] == 30 ||
		jogo[0] + jogo[4] + jogo[8] == 30 || jogo[2] + jogo[4] + jogo[6] == 30) {
		printf("Perdi :-(\n");
		return 1;
	}
	for (i = 0; i < 9; i++)
		if (jogo[i] == VAZIO)
			return 0;
	return 1;
}

int main() {
	int i, pid, primeiro, j;
	for (i = 0; i < 9; i++)
		signal(sinais[i], trataSinal);
	printf("O meu PID = %d \n", getpid());
	printf("PID do adversário?");
	scanf("%d", &pid);
	/*joga primeiro quem tiver o menor pid*/
	primeiro = (pid > getpid());
	while (1) {
		mostraJogo();
		if (primeiro)
			jogada(pid);
		if (terminou())
			break;
		printf("Aguarda jogada do adversário...\n");
		pause();
		mostraJogo();
		if (terminou())
			break;
		if (!primeiro)
			jogada(pid);
	}
}
