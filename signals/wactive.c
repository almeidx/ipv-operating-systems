#include <stdio.h>

int main() {
	printf("A iniciar uma espera activa...\n");
	while (1)
		;
	printf("...Esta mensagem nunca será impressa.\n");

	return 0;
}
