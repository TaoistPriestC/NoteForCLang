#include <stdio.h>
#include <arpa/inet.h>


void pton(){
    char ip[] = "192.168.3.103";
    unsigned int ip_int = 0;
    unsigned char *ip_ptr = (char *)&ip_int;

    inet_pton(AF_INET, ip, &ip_int);
    printf("点分十进制数字符串转化为一个整数:\n");
    printf("in_uint = %d\n", ip_int);
    printf("in_uint = %d.%d.%d.%d\n\n", ip_ptr[0], ip_ptr[1], ip_ptr[2], ip_ptr[3]);
}


void ntop(){
    char ip_str[16];
    unsigned char ip_ptr[] = {192, 168, 3, 103};

    inet_ntop(AF_INET, &ip_ptr, ip_str, 16);
    printf("四个整数转化为点分十进制数字符串:\n");
    printf("ip_uint = %d.%d.%d.%d\n", ip_ptr[0], ip_ptr[1], ip_ptr[2], ip_ptr[3]);
    printf("ip_uint = %s\n\n", ip_str);
}

int main(){
    pton();
    ntop();
    return 0;
}