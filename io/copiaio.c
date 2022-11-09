#include <unistd.h>

#define TAMANHO_DO_BUFFER 10

int main() {
	char buffer[TAMANHO_DO_BUFFER];
	int n;

	while ((n = read(STDIN_FILENO /*0*/, buffer, TAMANHO_DO_BUFFER)) > 0)
		write(STDOUT_FILENO /*1*/, buffer, n);

	return 0;
}
