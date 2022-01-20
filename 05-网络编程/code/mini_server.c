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


    // 填充服务器自身的信息
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    //绑定套接字与服务器信息结构体
    if(bind(sockfd,(struct sockaddr*)&serveraddr,addrlen) < 0){
        fprintf(stderr, "Fail to bind!\n");
        exit(EXIT_FAILURE);
    }

    //进行通信
    char buf[128];
    while(1){
        char txt[128];
        struct sockaddr_in clientaddr;
        if (recvfrom(sockfd, txt, sizeof(txt), 0, (struct sockaddr *)&clientaddr, &addrlen) < 0){
            fprintf(stderr, "Fail to recvfrom!\n");
            exit(EXIT_FAILURE);
        }
        printf("[%s - %d]:%s\n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), txt);
        strcat(txt, "<-_->");
        if (sendto(sockfd, txt, sizeof(txt), 0, (struct sockaddr *)&clientaddr, addrlen) < 0){
            fprintf(stderr, "Fail to sendto!\n");
            exit(EXIT_FAILURE);
        }
    }
    close(sockfd);
    return 0;
}