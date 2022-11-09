#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define exit_on_null(s, m)                                                                                             \
	if (s == NULL) {                                                                                                   \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main(int argc, char *argv[]) {
	char *line = NULL;
	ssize_t n = 0;

	/* Usage */
	if (argc != 2) {
		printf("Usage: %s <file name>\n", argv[0]);
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r"); /*Abre ficheiro para leitura*/

	exit_on_null(fp, "Erro na abertura");

	/*Leitura linha a linha*/
	while ((n = getline(&line, &n, fp)) != -1) {
		line[strlen(line) - 1] = '\0'; /*Retira \n do final da linha*/
		printf("%s\n", line);
	}

	fclose(fp);

	if (line) {
		free(line); /* liberta memoria reservada por getline */
	}

	return 0;
}
