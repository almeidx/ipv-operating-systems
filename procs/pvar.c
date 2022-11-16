#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int i = 10;

	if (fork() != 0) {
		/* processo pai*/
		i++;
		printf("PP:i=%d\n", i);
	} else {
		/* processo filho*/
		i += 2;
		printf("PF:i=%d\n", i);
	}

	i++;

	printf("i=%d\n", i);

	return 0;
}
