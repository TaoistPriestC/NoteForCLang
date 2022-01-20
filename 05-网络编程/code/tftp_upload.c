#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAXN  128
#define ERRLOG(msg){\
    fprintf(stderr, msg);\
    exit(EXIT_FAILURE);\
}

void upload(int sockfd, struct sockaddr_in serveraddr){
    char filename[MAXN];
    printf("Please enter the file name to upload:");
    scanf("%s", filename);

    int fd;
    if ((fd = open(filename, O_RDONLY)) < 0){
        if(errno == ENOENT){
            fprintf(stderr, "Fail %s doesn't exist, please enter again!\n", filename);
            return;
        }else{
            ERRLOG("Fail to open!\n");
        }
    }

    // 向服务器发送上传请求
    unsigned char txt[1024];
    socklen_t addrlen = sizeof(serveraddr);
    int txtlen = sprintf(txt, "%c%c%s%c%s%c", 0, 2, filename, 0, "octet", 0);
    if (sendto(sockfd, txt, txtlen, 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
        ERRLOG("Fail to sendto!\n");
    }

    ssize_t bytes;
    int recv_len, nums = 0;
    while(1){
        if ((recv_len = recvfrom(sockfd, txt, sizeof(txt), 0, (struct sockaddr *)&serveraddr, &addrlen)) < 0){
            ERRLOG("fail to recvfrom!\n");
        }
        if(txt[1] == 4 && nums == ntohs(*(unsigned short*)(txt + 2))){
            nums++;
            bytes = read(fd, txt + 4, 512);
            txt[1] = 3;
            *(unsigned short *)(txt + 2) = htons(nums);

            if(bytes == 512){
                if (sendto(sockfd, txt, bytes + 4, 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
                    ERRLOG("Fail to sendto!\n");
                }
            }else{
                if (sendto(sockfd, txt, bytes + 4, 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
                    ERRLOG("Fail to sendto!\n");
                }
                break;
            }
        }
    }
    printf("Upload finished!\n");
}


int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in serveraddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        ERRLOG("Fail to socket!\n");
    }
    
    // 填充服务器网络信息结构体
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(69);

    upload(sockfd, serveraddr);

    return 0;
}