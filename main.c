#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int
main(void)
{
	int socket_descriptor;
	struct sockaddr_in server;

	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor == -1)
	{
		printf("Could not create socket\n");
	}
	printf("Created socket\n");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );

	printf("Ready to connect\n");
	if (connect(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}

	puts("Connected");
	return 0;
}
