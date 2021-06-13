#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int
main(void)
{
	int socket_descriptor;
	struct sockaddr_in server;
	char *message, server_reply[2000];

	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor == -1)
	{
		printf("Could not create socket\n");
	}
	printf("Created socket\n");

	server.sin_addr.s_addr = inet_addr("142.250.204.46");
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );

	printf("Ready to connect\n");
	if (connect(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}

	puts("Connected");

	message = "GET / HTTP/1.1\r\n\r\n";
	if ( send(socket_descriptor, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Sent\n");

	if (recv(socket_descriptor, server_reply, 2000, 0) < 0)
	{
		puts("Recv failed");
	}

	puts("Reply received\n");
	puts(server_reply);

	return 0;
}
