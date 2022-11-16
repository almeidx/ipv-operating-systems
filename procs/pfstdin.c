#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	char s[100];

	if (fork()) {
		/* processo pai*/
		scanf("%[^\n]", s);
		printf("PP: s=%s\nVou terminar\n", s);
	} else {
		/* processo filho*/
		scanf("%[^\n]", s);
		printf("PF: s=%s\nVou terminar\n", s);
	}

	return 0;
}
