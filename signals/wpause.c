#include <stdio.h>
#include <unistd.h>

int main() {
	printf("A iniciar uma espera não activa (com pause)...\n");
	pause();
	printf("Esta mensagem não será impressa.\n");

	return 0;
}
