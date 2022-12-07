#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0666 /* permissões para outros utilizadores */
#define MAXMSG 100		/* assumir que chega */
#define MAXSALA 5		/* Número máximo de salas */
#define MAXPROC 5		/* Número máximo de proc. por sala*/

struct s_msg {
	long para; /* 1º campo: long obrigatório = PID destinatário*/
	int de;	   /* PID remetente*/
	int sala;  /*id sala*/
	char texto[MAXMSG];
};

/* Tab. de registo de utilizadores em cada sala */
int tsala[MAXSALA][MAXPROC];
