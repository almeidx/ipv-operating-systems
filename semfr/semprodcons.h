#include <stdio.h>
#include <stdlib.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define BUFFER 10
#define MAXTEXTO 50
#define MAXITENS 50
#define SEM_MUTEX 0
#define SEM_VAZIO 1
#define SEM_CHEIO 2

/*Organização da memoria partilhada*/
struct s_item { /*estrutura do item*/
	int id;
	char texto[MAXTEXTO];
};

struct s_shm {
	struct s_item itens[BUFFER];
	int in;	 /*Índice para colocar novo item = produtor*/
	int out; /*Índice para retirar item = consumidor*/
};
