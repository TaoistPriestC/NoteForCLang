#include <stdio.h>
#include <string.h>

// 假设现有布尔变量数量n，穷举所有其可能构成的组合
void tf(char arr[], int i, int n){
    if (i == n){
        puts(arr);
    }else{
        arr[i] = '0';
        tf(arr, i + 1, n);
        arr[i] = '1';
        tf(arr, i + 1, n);
    }
}


int main(){
    char list[256];
    memset(list, 0, sizeof(list));
    tf(list, 0, 3);
    return 0;
}