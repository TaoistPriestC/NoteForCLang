#include <stdio.h>
#define  SWAP(x,y,t)  ((t)=(x),(x)=(y),(y)=(t))

void selectSort(int arr[], int size){
    int minIdx, temp;
    for (int i = 0; i < size - 1; i++){
        minIdx = i;
        for (int j = i + 1; j < size; j++){
            if(arr[j] < arr[minIdx]){
                minIdx = j;
            }
        }
        SWAP(arr[minIdx], arr[i], temp);
    }
}

void printList(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d%s", arr[i], i == size - 1 ? "\n" : "\t");
    }
}

int binarySearch(int arr[], int size, int target){
    int lo = 0, hi = size, md;
    while(lo < hi){
        md = lo + (hi - lo) / 2;
        if(arr[md] == target){
            return md;
        }else if(arr[md] < target){
            lo = md;
        }else if(arr[md] > target){
            hi = md;
        }
    }
    return -1;
}

int main(){
    int list[] = {1, 5, 3, 2, 5, 8, 0};
    int listSize = sizeof(list) / sizeof(int);
    printList(list,listSize);
    selectSort(list, listSize);
    printList(list, listSize);
    printf("%d\n", binarySearch(list, listSize, 8));
    printf("%d\n", binarySearch(list, listSize, 5));
    return 0;
}