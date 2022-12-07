#include <stdio.h>
#include <unistd.h>

/* Implementa o equivalente a 'ls -la | wc' */
int main() {
	int p[2];
	pipe(p);
	if (!fork()) {	 /*filho (por exemplo)*/
		close(p[0]); /* fecha descritor de leitura do pipe*/
		close(1);	 /* fecha stdout */
		dup(p[1]);	 /* stdout <==> p[1] */
		close(p[1]); /* já não vai ser utilizado*/
		execlp("ls", "ls", "-la", NULL);
	} else {
		close(p[1]); /* fecha descritor de escrita do pipe*/
		close(0);	 /* fecha stdin */
		dup(p[0]);	 /* stdin <==> p[0] */
		close(p[0]); /* já não vai ser utilizado*/
		execlp("wc", "wc", NULL);
	}
}
