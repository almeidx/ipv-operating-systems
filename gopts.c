#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ./gopts -a -b arg1 arg2
// ./gopts -ab arg1 arg2
// ./gopts -abcvalc arg1
// ./gopts -c valc arg1

extern int optind, opterr, optopt;
extern char *optarg;

int main(int argc, char *argv[]) {
	int aflag = 0, bflag = 0, index, c;
	char *cvalue = NULL;

	opterr = 0; /* Para nada escrever em stderr */

	/* reconhece opções -a -b -c <valor>*/
	while ((c = getopt(argc, argv, ":abc:")) != -1) {
		switch (c) {
		case 'a':
			aflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case 'c':
			cvalue = optarg;
			break;
		case ':':
			printf("Opcao %c sem valor\n", optopt);
			break;
		case '?':
			printf("Opcao desconhecida: %c\n", optopt);
			break;
		default:
			printf("Erro!!\n");
			break;
		}
	}

	printf("Options: a= %d, b=%d, cvalue=%s\n", aflag, bflag, cvalue);

	/* restantes argumentos */
	for (index = optind; index < argc; index++)
		printf("Argumentos:%s\n", argv[index]);
}
