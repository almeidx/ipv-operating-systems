#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define TAMANHO 50

/*Organização da memória partilhada*/
struct s_shm {
	int tabela[TAMANHO];
};
