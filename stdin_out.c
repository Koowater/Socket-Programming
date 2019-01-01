// 리눅스에서 작동하는 표준 입출력을 이용한 간단한 프로그램의 예제이다.
#include <unistd.h> // 유닉스, 리눅스 계열 OS에서 사용되는 입출력 헤더
#include <string.h>
#include <stdio.h>

#define MAXLEN 80

int main(int argc, char **argv)
{
    char buf[MAXLEN];
    printf("Input Your Message : \n");
    memset(buf, 0x00, MAXLEN);
    read(0, buf, MAXLEN);

    printf("Your Message is : \n");
    write(1, buf, MAXLEN);
    return 0;
}