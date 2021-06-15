#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

/* 하나의 Host에 대해 저장되는 정보
 * struct hostent
 * {
 * 	char *h_name; // 정식 호스트 이름
 * 	char **h_aliases; // alias 리스트
 * 	int h_addrtype; // 주소 타입
 * 	int h_length; // 주소 길이
 * 	char **h_addr_list; // Name server 리스트
 * };
 */

/* 나중에 캐스팅할 in_addr struct 생김새
 * struct in_addr
 * {
 * 	unsigned long s_addr;
 * }
 */

int main(void)
{
	char *hostname = "www.google.com";
	char ip[100];
	struct hostent *hostentry;
	struct in_addr **addr_list;
	int i;

	/* gethostbyname 실패시 */
	if ( (hostentry = gethostbyname( hostname ) ) == NULL)
	{
		herror("gethostbyname");
		return 1;
	}


	/*  
	 * hostentry의 h_addr_list를 in_addr로 캐스팅
	 * 두개 다 IP주소를 long으로 갖고 있기 때문에
	 */
	addr_list = (struct in_addr **) hostentry->h_addr_list;

	for (i=0; addr_list[i] != NULL; i++)
	{
		printf("i: %d\n", i);
		strcpy(ip, inet_ntoa(*addr_list[i]) );
	}

	printf("%s resolved to %s", hostname, ip);
	return 0;

}
