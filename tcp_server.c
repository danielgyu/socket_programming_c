#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
	int socketfd, new_socket, c;
	struct sockaddr_in server, client;
	char* message;

	/* Socket 생성 단계 */
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
	{
		printf("Could not create socket\n");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	/* Bind 단계 */
	if (bind(socketfd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Bind failed\n");
	}
	puts("Bind done\n");

	/* Listen 단계 */
	listen(socketfd, 3);

	/* Accept 단계 */
	puts("Waiting for incoming connections...\n");
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socketfd, (struct sockaddr *)&client, (socklen_t*)&c);

	if (new_socket < 0)
	{
		perror("Accept failed\n");
	}
	puts("Connection accepted\n");

	/* 연결된 클라이언트에게 응답 */
	message = "Hello Client\n";
	write(new_socket, message, strlen(message));

	sleep(5);

	return 0;
}
