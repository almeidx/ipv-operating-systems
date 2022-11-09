#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// compile:
// gcc -c random.c
// gcc -o usage usage.c random.o

extern int aleatorio(int de, int ate);

int main(int argc, char *argv[]) {
	int tempo;

	if (argc != 3) {
		printf("Usage: %s <tempo mínimo> <tempo máximo>\n", argv[0]);
		exit(1);
	}

	srand(getpid());

	while (1) {
		tempo = aleatorio(atoi(argv[1]), atoi(argv[2]));
		printf("%d\n", tempo);
		sleep(tempo);
	}
}
