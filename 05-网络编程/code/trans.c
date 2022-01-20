#include <stdio.h>
#include <arpa/inet.h>
int main(){
    int a = 0x12345678;
    short b = 0x1234;

    /**
     * 转化过程是以字节为单位转化的 
     * 十六进制表示之下的两个数字才是一个字节
     * h: host
     * n: network
     * l: long
     * s: short
     */
    printf("%#x\n", htonl(a)); // 0x78563412
    printf("%#x\n", htons(b)); // 0x3412
}