#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int ret;
int main(int argc, char* argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage:%s<IP><Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in groupcastaddr;
    socklen_t addrlen = sizeof(groupcastaddr);

    if ((ret = sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "Fail to socket! ErrorCode:%d\n", ret);
        exit(EXIT_FAILURE);
    }

    
    // 设置加入多播组
    // 下面两个地址分别代表了组播IP地址(224.x.x.x - 239.x.x.x)、主机地址
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(argv[1]);
    mreq.imr_interface.s_addr = INADDR_ANY;
    
    if((ret = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) < 0){
        fprintf(stderr, "Fail to setsockopt! ErrorCode:%d\n", ret);
        exit(EXIT_FAILURE);
    }

    // 填充组播信息结构体
    groupcastaddr.sin_family = AF_INET;
    groupcastaddr.sin_addr.s_addr = inet_addr(argv[1]);
    groupcastaddr.sin_port = htons(atoi(argv[2]));


    // 再把广播信息结构体与套接字绑定
    if ((ret = bind(sockfd, (struct sockaddr *)&groupcastaddr, addrlen)) < 0){
        fprintf(stderr, "Fail to bind! ErrorCode:%d\n", ret);
        exit(EXIT_FAILURE);
    }


    char buf[128];
    struct sockaddr_in sendaddr;
    while(1){
        if ((ret = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&sendaddr, &addrlen)) < 0){
            fprintf(stderr, "Fail to recvfrom! ErrorCode:%d\n", ret);
            exit(EXIT_FAILURE);
        }
        printf("[%s - %d]: %s\n", inet_ntoa(sendaddr.sin_addr), ntohs(sendaddr.sin_port), buf);
    }

    return 0;
}