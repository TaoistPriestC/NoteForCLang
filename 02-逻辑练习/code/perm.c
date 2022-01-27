#include <stdio.h>
#define  SWAP(x,y,t)  ((t)=(x),(x)=(y),(y)=(t))


void perm(char arr[], int i, int size){
    if (i == size){
        for (int i = 0; i < size; i++){
            printf("%c%s", arr[i], i == size - 1 ? "\n" : "\t");
        }
    }else{
        char temp;
        for (int j = i; j < size; j++){
            SWAP(arr[i], arr[j], temp);
            perm(arr, i + 1, size);
            SWAP(arr[i], arr[j], temp);
        }
    }
}

int main(){
    char list[] = {'a', 'b', 'c', 'd'};
    perm(list, 0, sizeof(list) / sizeof(char));
    return 0;
}