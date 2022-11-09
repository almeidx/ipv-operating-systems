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
	si.sin_addr.s_addr = htonl(0x7f000001);
	si.sin_port = htons(1337);

	socklen_t si_len = sizeof(si);

	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) {
		perror("socket");
		return 1;
	}

	if (connect(sfd, (struct sockaddr *)&si, si_len) < 0) {
		perror("connect");
		return 1;
	}

	char buffer[1024];

	ssize_t recvd = recv(sfd, buffer, sizeof(buffer), 0);
	printf("Received %zd bytes: %s", recvd, buffer);

	close(sfd);

	return 0;
}
