#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// ./regex \[0-9]\{1,2}-\[0-9]\{1,2}-\[0-9]\{4\} date.txt

#define exit_on_null(s, m)                                                                                             \
	if (s == NULL) {                                                                                                   \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *line = NULL;
	ssize_t n = 0;
	regex_t re;

	/* Usage */
	if (argc != 3) {
		printf("Usage: %s <pattern> <file name>\n", argv[0]);
		exit(1);
	}

	/*Abre ficheiro para leitura*/
	fp = fopen(argv[2], "r");
	exit_on_null(fp, "Erro na abertura do ficheiro");

	/*Prepara exp. regular*/
	n = regcomp(&re, argv[1], REG_EXTENDED);

	/*Leitura linha a linha*/
	while ((n = getline(&line, &n, fp)) != -1) {
		line[strlen(line) - 1] = '\0'; /*Retira \n do final da linha*/
		if (regexec(&re, line, 0, NULL, 0) == 0) {
			printf("%s\n", line);
		}
	}

	fclose(fp);

	/*Limpa memoria*/
	if (line) {
		free(line);
	}

	regfree(&re);

	return 0;
}
