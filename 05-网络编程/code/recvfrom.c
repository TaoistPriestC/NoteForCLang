#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAXN 128
int main(int argc, char *argv[]){
   // ./recvfrom.out 192.168.3.78 8080
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

    // 再把服务器的网络信息结构体填充
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    // 绑定
    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1){
        fprintf(stderr, "Fail to bind!\n");
        exit(EXIT_FAILURE);
    }

    // 接受信息
    char buf[MAXN];
    struct sockaddr_in clientaddr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    while(1){
        if (recvfrom(sockfd, buf, MAXN, 0, (struct sockaddr *)&clientaddr, &addrlen) == -1){
            fprintf(stderr, "Fail to recvfrom!\n");
            exit(EXIT_FAILURE);
        }
        printf("IP: %s, Port:%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
        printf("From client: %s\n", buf);
    }
    return 0;
}