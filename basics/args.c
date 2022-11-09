#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("%d argumentos na linha de comando, que são:\n", argc);

	for (int i = 0; i < argc; i++) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	return 0;
}
