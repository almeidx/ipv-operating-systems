#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	struct sockaddr_in si = {0};
	si.sin_family = AF_INET;
	si.sin_port = htons(1337);

	struct sockaddr ci = {0};
	socklen_t si_len = sizeof(si);
	socklen_t ci_len = sizeof(ci);

	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) {
		perror("socket");
		return 1;
	}

	if (bind(sfd, (struct sockaddr *)&si, si_len) < 0) {
		perror("bind");
		return 1;
	}

	if (listen(sfd, 0) < 0) {
		perror("socket");
		return 1;
	}

	int cfd = accept(sfd, &ci, &ci_len);
	if (cfd < 0) {
		perror("accept");
		return 1;
	}

	char *hello = "Hello World!\n";
	ssize_t sent = send(cfd, (void *)hello, strlen(hello), 0);

	printf("Sent %zd bytes\n", sent);

	close(cfd);

	return 0;
}
