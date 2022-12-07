#include <stdio.h>
#include <unistd.h>

int main() {
	int pedido[2], resposta[2], n;
	pipe(pedido);
	pipe(resposta);
	if (!fork()) { /* filho */
		n = -1;
		while (n != 0) {
			printf("N (0 para terminar)?");
			scanf("%d", &n);
			if (n != 0) {
				printf("O dobro de %d é ", n);
				write(pedido[1], &n, sizeof(int));
				read(resposta[0], &n, sizeof(int));
				printf("%d\n", n);
			}
		}
	} else {			  /* pai */
		close(pedido[1]); /*Essencial!!*/
		while (read(pedido[0], &n, sizeof(int)) > 0) {
			n *= 2;
			write(resposta[1], &n, sizeof(int));
		}
		printf("Já não haverá mais pedidos, vou terminar\n");
	}
}
