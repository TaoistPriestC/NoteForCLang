#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage:%s<IP><Port>", argv[0]);
        exit(EXIT_FAILURE);
    }
    int sockfd;
    struct sockaddr_in broadcataddr;
    socklen_t addrlen = sizeof(broadcataddr);

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "Fail to socket!\n");
        exit(EXIT_FAILURE);
    }

    broadcataddr.sin_family = AF_INET;
    broadcataddr.sin_addr.s_addr = inet_addr(argv[1]);
    broadcataddr.sin_port = htons(atoi(argv[2]));

    if (bind(sockfd, (struct sockaddr *)&broadcataddr, addrlen) < 0){
        fprintf(stderr, "Fail to bind!\n");
        exit(EXIT_SUCCESS);
    }

    char txt[32];
    struct sockaddr_in sendaddr;

    while(1){
        if (recvfrom(sockfd, txt, sizeof(txt), 0, (struct sockaddr *)&sendaddr, &addrlen) < 0){
            fprintf(stderr,"Fail to recvfrom!\n");
            exit(EXIT_FAILURE);
        }
        txt[strlen(txt)] = '\0';
        printf("[From IP:%s - Port:%d]:%s\n", inet_ntoa(sendaddr.sin_addr), ntohs(sendaddr.sin_port), txt);
        memset(txt, 0, sizeof(txt));
    }

    return 0;
}