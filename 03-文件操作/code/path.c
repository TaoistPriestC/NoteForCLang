#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 自行实现一个算法, 
// 要求能把相对路径转化为绝对路径
// 输入路径: /home/abs/../temp/new/../ 
// 输出路径: /home/temp

#define MAXN 128

char tmp[MAXN];
char *input[2 * MAXN]; 
char *output[2 * MAXN];

int top_tmp = 0;
int top_input = 0;
int top_output = 0;

char * toString(char* arr){
    int len = strlen(arr);
    char *ptr = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++){
        ptr[i] = arr[i];
    }
    ptr[len] = '\0';
    return ptr;
}

void pathChange(const char * str){
    int len = strlen(str);
    for (int i = 0; i < len; i++){
        if(str[i]!='/'){
            tmp[top_tmp++] = str[i];
        }else{
            if(strlen(tmp) > 0){
                input[++top_input] = toString(tmp);
                memset(tmp, 0, sizeof(tmp));
                top_tmp = 0;
            }
        }
    }

    // 打印每一个子路径, 看看对不对
    // for(int i = 1; i <= top_input; i++){
    //     puts(input[i]);
    // }
    

    // 主要思想是使用数组模拟栈结构,input和output在此便是充当栈
    while(top_input){
        if(strcmp(input[top_input],"..")){
            output[++top_output] = input[top_input--];
        }else{
            input[top_input--];
            input[top_input--];
        }
    }

    while (top_output){
        printf("/%s", output[top_output--]);
    }
    printf("\n");
}


int main(){
    pathChange("/home/abs/../temp/new/../");
    return 0;
}