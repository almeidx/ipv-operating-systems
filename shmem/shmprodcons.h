#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define BUFFER 10
#define MAXTEXTO 50
#define MAXITENS 50

/* Organização da memória partilhada*/
struct s_item { /*estrutura do item*/
	int id;
	char texto[MAXTEXTO];
};

struct s_shm {
	struct s_item itens[BUFFER];
	int in;		 /*Índice para colocar novo item = produtor*/
	int out;	 /*Índice para retirar item = consumidor*/
	int counter; /* número de itens no buffer*/
};
