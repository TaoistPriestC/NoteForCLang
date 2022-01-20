#include<stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
//
int main(int argc, char *argv[]){
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
        perror("fail to socket");
        exit(EXIT_FAILURE);
    }
    /** int socket(int af, int type, int protocol)  
     *  自左向右三个参数的常用取值:
     *  @param: AF_INET(使用ipv4), AF_INET6(使用ipv6), AF_UNIX(Unix本地通信)
     *  @param: SOCK_STREAM(TCP), SOCK_DGRAM(UDP), SOCK_RAW(原始套接字)
     *  @param: 0, IPPROTO_TCP, IPPROTO_UDP
     * 
     * 其中AF代表了Address Family,亦可使用PF(Protocol Family)前缀开头, 两者是等价的,
     * 任何进程在开启之初都将分配0/1/2三个文件描述符, 接下来再分配便从3开始！
     * 
     */
    printf("sockfd = %d\n", sockfd); //打印结果 3 
    return 0;
}