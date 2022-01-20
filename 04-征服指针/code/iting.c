#include <stdio.h>
#include <stdlib.h>

int row;
int (*(buf[]))  = {
    (int []){1, 2, 3, 4},
    (int []){1, 2},
    (int []){3, 4, 5}
};

/** 这是一个与上文等价的写法,其实就是存储了int指针的数组
    int* buf[] = {
        (int []){1, 2, 3, 4},
        (int []){1, 2},
        (int []){3, 4, 5}
    };
 */

int main(){
    row = 0;
    for (int i = 0; i < 4; i++){
        printf("Layer[%d][%d], Address: %p, Value:%d\n", row, i, &buf[row][i], buf[row][i]);
    }
    printf("\n");

    row = 1;
    for (int i = 0; i < 2; i++){
        printf("Layer[%d][%d], Address: %p, Value:%d\n", row, i, &buf[row][i], buf[row][i]);
    }
    printf("\n");

    row = 2;
    for (int i = 0; i < 5; i++){
        printf("Layer[%d][%d], Address: %p, Value:%d\n", row, i, &buf[row][i], buf[row][i]);
    }
    printf("\n");

    printf("%ld\n", sizeof(buf));
    return 0;
}