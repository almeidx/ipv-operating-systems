#include <stdio.h>
#include <unistd.h>

#define TEMPO 10

int main() {
	printf("A iniciar uma espera não activa (com sleep)...\n");
	sleep(TEMPO);
	printf("Terminou o tempo de %d \n", TEMPO);

	return 0;
}
