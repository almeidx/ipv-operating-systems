#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define exit_on_error(s, m)                                                                                            \
	if (s < 0) {                                                                                                       \
		perror(m);                                                                                                     \
		exit(1);                                                                                                       \
	}

#define PERMISSOES 0600 /* admita-se que serve para o exemplo */
#define TAMANHO 100

struct s_msg {
	long tipo; /* 1º campo: long: obrigatório (destinatário)*/
	char texto[TAMANHO];
}; /* o que se quiser, desde que escritores e leitores estejam de acordo */
