#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
	int i = 0;

	printf("Variáveis de ambiente passadas ao processo:\n");

	while (envp[i] != NULL) {
		printf("%s\n", envp[i]);
		i++;
	}
}
