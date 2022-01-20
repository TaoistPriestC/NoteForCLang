#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage:%s<IP><Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in groupcastaddr;
    socklen_t addrlen = sizeof(groupcastaddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "Fail to scoket!\n");
        exit(EXIT_FAILURE);
    }

    // 填充组播信息结构体
    // IP地址取值范围: 224.x.x.x - 239.x.x.x
    groupcastaddr.sin_family = AF_INET;
    groupcastaddr.sin_addr.s_addr = inet_addr(argv[1]);
    groupcastaddr.sin_port = htons(atoi(argv[2]));


    char buf[128];
    while(1){
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = '\0';
        // 发送消息的一方要记得把结尾的换行符换成结束符号
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&groupcastaddr, addrlen) < 0){
            fprintf(stderr, "Failed to send!\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}