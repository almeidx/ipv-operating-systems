#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXMATCH 10
#define MAXSTR 100
#define exit_on_null(s, m)                                                                                             \
	if (s == NULL) {                                                                                                   \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

void substr(char *sdest, char *sfrom, int first, int last) {
	strncpy(sdest, sfrom + first, last - first);
	sdest[last - first] = '\0';
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char *line = NULL;
	ssize_t n = 0;
	regex_t re;
	regmatch_t match[MAXMATCH];
	size_t nmatch;
	int i;
	char s[MAXSTR];

	/* Usage */
	if (argc != 3) {
		printf("Usage: %s <pattern> <file name>\n", argv[0]);
		exit(1);
	}

	/*Abre ficheiro para leitura*/
	fp = fopen(argv[2], "r");
	exit_on_null(fp, "Erro na abertura\n");

	/*Prepara exp. regular*/
	n = regcomp(&re, argv[1], REG_EXTENDED);

	/*Leitura linha a linha*/
	while ((n = getline(&line, &n, fp)) != -1) {
		line[strlen(line) - 1] = '\0'; /*Retira \n do final da linha*/

		if (regexec(&re, line, MAXMATCH, &match[0], 0) == 0) {
			printf("%s\n", line);

			for (i = 1; i < MAXMATCH; i++) {
				if (match[i].rm_eo != -1) {
					substr(s, line, match[i].rm_so, match[i].rm_eo);
					printf("match[%d]:%s\n", i, s);
				}
			}
		}
	}

	fclose(fp);

	/*Liberta memoria*/
	if (line)
		free(line);

	regfree(&re);

	return 0;
}
