#include <stdio.h>
#include <stdlib.h>

#define  MAXN  256
#define  SWAP(x,y,t)  ((t)=(x),(x)=(y),(y)=(t))

int temp[MAXN];

int  _mergeSort(int list[], int listSize, int lo, int hi){
    if (lo >= hi)
        return 0;
    
    int md = lo + (hi - lo) / 2;
    int beg1 = lo, end1 = md, beg2 = md + 1, end2 = hi;

    int ltr = _mergeSort(list, listSize, beg1, end1); // 左侧数组的逆序对
    int rtr = _mergeSort(list, listSize, beg2, end2); // 右侧数组的逆序对
    
    if (list[md] < list[md + 1]){
        return ltr + rtr;
    }

    // 如果不满足list[beg1] < list[beg2]则在右侧的beg2指针所指元素更小
    // 说明此时左侧数组beg1指针开始往右直至end1所有元素都大于list[beg2],并与之构成逆序对
    int k = lo, cnt = 0;
    while( beg1 <= end1 && beg2 <= end2){
        // temp[k++] = list[beg1] < list[beg2] ? list[beg1++] : list[beg2++];
        if(list[beg1] < list[beg2]){
            temp[k++] = list[beg1++];
        }else{
            temp[k++] = list[beg2++];
            cnt += (end1 - beg1 + 1);
        }   
    }
    while (beg1 <= end1) temp[k++] = list[beg1++];
    while (beg2 <= end2) temp[k++] = list[beg2++];
    
    for (k = lo; k <= hi; k++){
        list[k] = temp[k];
    }

    return ltr + rtr + cnt;
}

int  mergeSort(int list[], int listSize){
    return _mergeSort(list, listSize, 0, listSize - 1);
}

void printList(int list[], int listSize){
    for (int i = 0; i < listSize; i++){
        printf("%d%s", list[i], (i != listSize - 1 ? "\t" : "\n"));
    }
}

int list[] = {3, 5, 4, 2, 1, 8, -1};
int main(){
    int listSize = sizeof(list) / sizeof(int);
    printList(list, listSize);
    printf("逆序对数量:%d\n", mergeSort(list, listSize));
    printList(list, listSize);
}