#include <stdio.h>
#include <string.h>


// 去重算法,下面代码本质是一个快慢双指针算法
// 其中j与j分别代表慢指针与快指针, i先走, j用来判断是否出现重复
int list[] = {1, 2, 2, 3, 4, 5, 5, 5, 6};
int deduplicate(int list[], int listSize){
    if(listSize < 2)
        return listSize;
    int j = 0;
    for (int i = 1; i < listSize; i++){
        if (list[j] != list[i]){
            list[++j] = list[i];
        }
    }
    return j + 1;
}

void printList(int list[],int listSize){
    for (int i = 0; i < listSize; i++){
        printf("%d%s", list[i], (i != listSize - 1 ? "\t" : "\n"));
    }
}

int main(){

    // 去重之前
    int oldSize = sizeof(list) / sizeof(int);
    printList(list, oldSize);

    // 去重之后
    int newSize = deduplicate(list, sizeof(list) / sizeof(int));
    printList(list, newSize);

    return 0;
}