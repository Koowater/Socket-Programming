#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	struct sockaddr_in serveraddr;
	int server_sockfd;
	int client_len;
	char buf[MAXLINE];

	if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{	
		// socket 함수로 소켓 생성
		perror("error :");
		return 1;
	}

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(atoi(argv[1]));

	client_len = sizeof(serveraddr);

	if(connect(server_sockfd, (struct sockaddr *)&serveraddr, client_len) == -1)
	{
		// connect 함수로 서버에 연결 시도
		perror("connect error :");
		return 1;
	}

	memset(buf, 0x00, MAXLINE);
	read(0, buf, MAXLINE); // 키보드 입력을 기다린다.
	if(write(server_sockfd, buf, MAXLINE) <= 0)
	{
		// 입력 받은 데이터를 서버로 전송한다.
		perror("read error :");
		return 1;
	}
	close(server_sockfd);
	printf("read : %s", buf);
	return 0;
}
