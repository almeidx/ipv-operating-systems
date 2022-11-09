#include <stdio.h>
#include <unistd.h>

int main() {
	printf("A execução vai ser continuada por outro programa.\n");
	printf("Adeus.\n");
	execl("/bin/ls", "ls", "-la", NULL);

	/*ou*/
	/* execlp("ls", "ls", "-l", NULL);*/
	/* Nota: <path|executável>, argv[0], argv[1], argv[2]...*/

	printf("Esta linha nao vai ser impressa!\n");
}
