#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage:%s<IP><Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    // 填入服务器网络信息    
    int sockfd;
    struct sockaddr_in broadcataddr;
    socklen_t addrlen = sizeof(broadcataddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, )) < 0){
        fprintf(stderr, "Fail to socket!\n");
        exit(EXIT_FAILURE);
    }

    // 设置允许发送广播权限
    int on = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) < 0){
        fprintf(stderr, "Fail to setsockopt\n");
        exit(EXIT_FAILURE);
    }

    broadcataddr.sin_family = AF_INET;
    broadcataddr.sin_addr.s_addr = inet_addr(argv[1]);
    broadcataddr.sin_port = htons(atoi(argv[2]));

    char buf[128];
    while(1){
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&broadcataddr, addrlen) < 0){
            fprintf(stderr, "Fail to sendto!\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}