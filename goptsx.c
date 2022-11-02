#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ./goptsx -xfkd -d -c valc arg1
// ./goptsx -xfkd -dvald -c valc arg1

extern int optind, opterr, optopt;
extern char *optarg;

int main(int argc, char *argv[]) {
	int xflag = 0, fflag = 0, index, c;
	char *cvalue = NULL, *dvalue = NULL;

	opterr = 0; /* Para nada escrever em stderr */

	while ((c = getopt(argc, argv, "xfc:d::")) != -1) {
		switch (c) {
		case 'x':
			xflag = 1;
			break;
		case 'f':
			fflag = 1;
			break;
		case 'c':
			cvalue = optarg;
			break;
		case 'd':
			dvalue = optarg;
			break;
		case ':':
			printf("Opcao %c sem valor\n", optopt);
			break;
		case '?':
			printf("Opcao desconhecida: %c\n", optopt);
			break;
		default:
			printf("Erro!! %c\n", c);
			break;
		}
	}

	printf("Options: x= %d, f=%d, cvalue=%s, dvalue=%s\n", xflag, fflag, cvalue, dvalue);

	/* restantes argumentos */
	for (index = optind; index < argc; index++)
		printf("Argumentos:%s\n", argv[index]);
}
