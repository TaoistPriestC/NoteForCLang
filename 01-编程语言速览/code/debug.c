#include<stdio.h>

#define MAXN  (5)


void hello(){
    printf("Hello~\n");
}

int main(){
    int arr[MAXN] = {1, 2, 3, 4, 5};
    for (int i = 0; i < MAXN; i++){
        printf("%d\n", arr[i]);
    }
    hello();
    return 0;
}