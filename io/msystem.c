#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <programa a executar com system()>\n", argv[0]);
		exit(1);
	}

	size_t len = 0;
	for (int i = 1; i < argc; i++) {
		len += strlen(argv[i]) + 1;
	}

	char *cmd = (char *)malloc(len * sizeof(char) + 1);
	cmd[0] = '\0';

	for (int i = 1; i < argc; i++) {
		strcat(cmd, argv[i]);
		strcat(cmd, " ");
	}

	system(cmd);

	free(cmd);

	printf("\nTerminado\n");
}
