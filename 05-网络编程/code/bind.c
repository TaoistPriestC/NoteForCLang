#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// 一般服务器都需要执行bind函数
int main(int argc, char *argv[]){
    // ./bind.out 192.168.3.78 8080
    if(argc < 3){
        fprintf(stderr, "Usage:<%s><ip><port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 创建套接字
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        fprintf(stderr, "Fail to socket!\n");
        exit(EXIT_FAILURE);
    }


    // 再把服务器的网络信息填充放入sockaddr_in结构体
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    // 绑定网络信息结构体与套接字
    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1){
        fprintf(stderr, "Fail to bind!\n");
        exit(EXIT_FAILURE);
    }

    // 通常来说只要端口未被占用便能成功
    // 如果成功建立服务器则打印绑定成功的信息
    printf("Successfully bound!\n");
    return 0;
}