#include <stdio.h>
#include <sys/socket.h>

int
main(int argc, char *argv[])
{
	int socket_descriptor;
	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}

	return 0;
}
