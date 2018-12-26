#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXBUF 1024

int main(int argc, char **argv)
{
	int server_sockfd, client_sockfd;
	int client_len, n;
	char buf[MAXBUF];
	struct sockaddr_in clientaddr, serveraddr;

	client_len = sizeof(clientaddr); // 클라이언트 주소의 길이

	if((server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		// socket 함수로 소켓 생성
		perror("socket error :");
	}

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY(0.0.0.0), 즉 모든 주소에 대해 연결을 기다린다.
	serveraddr.sin_port = htons(atoi(argv[1])); // port를 설정한다.

	bind(server_sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)); // 위의 설정들을 적용한다.
	listen(server_sockfd, 5); // 수신 대기열을 정한다.

	while(1)
	{
		memset(buf, 0x00, MAXBUF);
		client_sockfd = accept(server_sockfd, (struct sockaddr *) &clientaddr, &client_len);
		printf("New Client Connect: %s\n", inet_ntoa(clientaddr.sin_addr));
		if((n = read(client_sockfd, buf, MAXBUF)) <= 0)
		{
			close(client_sockfd);
			continue;
		}
		else
		{
			if(strncmp(buf, "shutdown", 8) == 0) // "shutdown" 문자열을 입력받으면 서버를 종료한다.
			{
				printf("Shut Down...\n");
				close(client_sockfd);
				break;
			}
			printf("read data : %s", buf); // 읽은 데이터를 출력한다.
		}
		if(write(client_sockfd, buf, MAXBUF) <= 0)
		{
			perror("write error :");
			close(client_sockfd);
		}
		close(client_sockfd);
	}
	close(server_sockfd);
	return 0;
}
