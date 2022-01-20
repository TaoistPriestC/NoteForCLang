#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage:<%s><IP><Port>!\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int sockfd;
    struct sockaddr_in serveraddr;
    socklen_t addrlen = sizeof(serveraddr);

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "Fail to socket!\n");
        exit(EXIT_FAILURE);
    }

    // 客户端通常无需自己指定IP与Port,因为系统自动分配
    // ...

    // 填充想要沟通的服务器的网络信息结构体
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    //进行通信
    char buf[128];
    while(1){
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
            fprintf(stderr, "Fail to sendto!");
            exit(EXIT_FAILURE);
        }

        char txt[128];
        if (recvfrom(sockfd, txt, sizeof(txt), 0, (struct sockaddr *)&serveraddr, &addrlen) < 0){
            fprintf(stderr, "Fail to sendto!");
            exit(EXIT_FAILURE);
        }
        printf("From server: %s\n", txt);
    }

    close(sockfd);
    return 0;
}