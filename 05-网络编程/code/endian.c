#include<stdio.h>
#include<stdlib.h>

typedef union judge{
    int data4byte;
    char data1byte;
} judge;

int main(){
    judge un;
    un.data4byte = 0x12345678;
    printf("data4byte = %#x\n", un.data4byte);
    printf("data1byte = %#x\n", un.data1byte);
    if (un.data1byte == 0x78){
        printf("This is the small end storage format!\n");
    }else{
        printf("This is the big end storage format!\n");
    }
    return 0;
}