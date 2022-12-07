#include <stdio.h>
#include <stdlib.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define MAXTEXTO 50
#define SEM_MUTEX 0
#define SEM_ESCRITA 1

/*Organização da memória partilhada*/
struct s_shm {
	int NLeitores;
	char texto[MAXTEXTO];
};
