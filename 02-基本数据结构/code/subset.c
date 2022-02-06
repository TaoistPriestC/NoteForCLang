#include <stdio.h>
#include <string.h>

#define MAXN 256
char powerset[MAXN][MAXN];
char bitVec[MAXN];

// 位向量构造法获取子集
void subset(char bitv[], char list[], int curr, int size){
    if (curr == size){
        for (int i = 0; i < curr; i++){
            if (bitv[i] == '1'){
                printf("%c", list[i]);
            }
        }
        return;
    }
    bitv[curr] = '0';
    subset(bitv, list, curr + 1, size);
    bitv[curr] = '1';
    subset(bitv, list, curr + 1, size);
}


int main(){
    char list[] = {'a', 'b', 'c'};
    subset(bitVec, list, 0, sizeof(list) / sizeof(char));
    return 0;
}