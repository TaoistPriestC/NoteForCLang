#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MAXN 128

//使用IP:192.168.3.78,端口:8080创建一个客户机,用于发送信息
int main(int argc, char * argv[]){
    // ./sendto.out 192.168.3.78 8080
    if(argc < 3){
        fprintf(stderr, "Usage:<%s><ip><port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // 首先创建套接字
    int socketfd;
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        fprintf(stderr, "Fail to socket!\n");
        exit(EXIT_FAILURE);
    }
    printf("socketfd = %d\n", socketfd);

    // 再把服务器网络信息填充放入sockaddr_in结构体
    struct sockaddr_in serveraddr;
    socklen_t addrlen = sizeof(serveraddr);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    
    // 发送数据
    char buf[MAXN];
    while(1){
        fgets(buf, MAXN, stdin);
        buf[strlen(buf) - 1] = '\0';
        if (sendto(socketfd, buf, MAXN, 0, (struct sockaddr *)&serveraddr, addrlen) == -1){
            fprintf(stderr, "Fail to sendto!\n");
            exit(EXIT_FAILURE);
        }
    }

    // 关闭套接字文件描述符
    close(socketfd);

    return 0;
}