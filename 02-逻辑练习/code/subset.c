#include <stido.h>
#include <string.h>

char powerset[256][256];

void subset(char arr[], int size){
    int pSize = 1;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < pSize; j++){
            strcat(powerset[++pSize], arr[i]);
        }
    }
}

int main(){
    char list[] = {'a', 'b', 'c'};

    return 0;
}