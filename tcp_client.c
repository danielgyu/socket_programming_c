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

	// TCP 소켓 생성
	socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	// 실패했을 경우
	if (socket_descriptor == -1)
	{
		printf("Could not create socket\n");
	}
	printf("Created socket\n");

	// 구글 서버에 연결 요청하기 위한 정보 추가
	// server(type sockaddr_in)에 IP주소, 프로토콜, 포트
	server.sin_addr.s_addr = inet_addr("142.250.204.46");
	server.sin_family = AF_INET;
	server.sin_port = htons( 80 );

	// connect 시스템콜을 통한 연결 시도
	// -1은 실패했을 때의 리턴값
	printf("Ready to connect\n");
	if (connect(socket_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Connect error");
		return 1;
	}

	puts("Connected");

	// 구글 서버에 메시지 보내기(GET)
	message = "GET / HTTP/1.1\r\n\r\n";
	if ( send(socket_descriptor, message, strlen(message), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Sent\n");

	// 보낸 메시지에 대해 응답 받기
	if (recv(socket_descriptor, server_reply, 2000, 0) < 0)
	{
		puts("Recv failed");
	}

	puts("Reply received\n");
	puts(server_reply);

	return 0;
}
