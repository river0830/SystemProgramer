#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int server_socket(void)
{
	int socketfd, n;
	struct sockaddr_in servaddr;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(struct sockaddr_in));

	return 0;
}

