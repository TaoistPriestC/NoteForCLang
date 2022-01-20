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
void download(int sockfd, struct sockaddr_in serveraddr){
    char filename[MAXN];
    printf("Please enter the file name to download:");
    scanf("%s", filename);

    // 向服务器发送一个下载请求
    unsigned char txt[1024];
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int texlen = sprintf(txt, "%c%c%s%c%s%c", 0, 1, filename, 0, "octet", 0);
    if (sendto(sockfd, txt, texlen, 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
        fprintf(stderr, "Fail to sendto!\n");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes;
    int fd, flags = 0, num = 0;
    while(1){
        // 接受服务器发送过来的数据, bytes接受返回数据的字节数
        if ((bytes = recvfrom(sockfd, txt, sizeof(txt), 0, (struct sockaddr *)&serveraddr, &addrlen)) < 0){
            fprintf(stderr, "Fail to recvfrom!\n");
            exit(EXIT_FAILURE);
        }
        // 号码5代表出错了,号码3代表数据包
        // 数据包/错误信息 = 2B操作码 + 2B块编号+512B数据(或为若干错误信息)
        if (txt[1] == 5){
            fprintf(stderr, "Error:%s\n", txt + 4);
            exit(EXIT_FAILURE);
        }else if(txt[1] == 3){
            if(flags == 0){
                // Linux打开文件的操作不同于Windows,这点需要查阅文档
                if((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0){
                    fprintf(stderr, "Fail to open!\n");
                    exit(EXIT_FAILURE);
                }
                flags = 1;
            }

            // 对比编号与的接收数据的大小将下载的文件内容写入本地文件, 如果文件大小小于516说明是最后一个数据块
            if ((num + 1 == ntohs(*(unsigned short *)(txt + 2))) && (bytes == 516)){
                num = ntohs(*(unsigned short *)(txt + 2));
                if (write(fd, txt + 4, bytes - 4) < 0){
                    fprintf(stderr, "Fail to write!\n");
                    exit(EXIT_FAILURE);
                }
                // 文件写入完毕之后向服务器发送ACK, 其对应号码4
                txt[1] = 4;
                if (sendto(sockfd, txt, 4, 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
                    fprintf(stderr, "Fail to sendto!\n");
                    exit(EXIT_FAILURE);
                }
            }else if((num + 1 == ntohs(*(unsigned short *)(txt + 2))) && (bytes < 516)){
                if (write(fd, txt + 4, bytes - 4) < 0){
                    fprintf(stderr, "Fail to write!\n");
                    exit(EXIT_FAILURE);
                }
                // 文件写入完毕之后向服务器发送ACK, 其对应号码4
                txt[1] = 4;
                if (sendto(sockfd, txt, 4, 0, (struct sockaddr *)&serveraddr, addrlen) < 0){
                    fprintf(stderr, "Fail to sendto!\n");
                    exit(EXIT_FAILURE);
                }
                printf("Download Finished!\n");
                return;
            }
        }

    }
}



int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "Usage:%s<Server IP>!\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    // 创建套接字
    int sockfd;
    struct sockaddr_in serveraddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "Fail to socket!\n");
        exit(EXIT_FAILURE);
    }

    // 填充服务器网络信息结构体
    // 端口号是固定的 69
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(69);

    download(sockfd, serveraddr);

    return 0;
}
