#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	printf("E vai um\n");
	fork();
	printf("E vão dois\n");

	return 0;
}
