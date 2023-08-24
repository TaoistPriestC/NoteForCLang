#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"



/**
 *  仅在使用 -DTEST 命令行参数，才会定义 main 函数部分的代码并且执行其中单元测试
 *  gcc vector.c -o a -DTEST && ./a
 */ 
#ifdef TEST
int main() {   
    printf("Unit tset!\n");
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Vector *nums = new_vector_fromArray(10, sizeof(int), arr);
    for (int i = 0; i < nums->len; i++){
        printf("%d\n", *(int*)vector_at(nums, i));
    }
    return 0;
}
#endif


// 基础构造函数
Vector* new_vector(int len, int each_size){
    Vector *vec = malloc(sizeof(Vector));

    // 初始化扩容因子/单个元素长度
    vec->factor = 1.5;
    vec->each_size = each_size;

    // 初始化底层数组的长度与容量
    vec->len = len;
    vec->cap = vec->factor * len;

    // 分配一个无类型数组
    vec->array = calloc(vec->cap, each_size);

    return vec;
}

Vector* new_vector_fromArray(int len, int each_size, void* src) {
    Vector *vec = new_vector(len, each_size);
    memcpy(vec->array, src, len * each_size);
    return vec;
}


void delete_vector(Vector *vec){
    free(vec->array);
    free(vec);
}

void* vector_at(Vector *vec, int i){
    // 检查下标是否有效，如果有效转成 char 类型计算偏移量，否则进行错误处理
    if (i >= 0 && i < vec->len) { 
        return (char*)vec->array + i * vec->each_size;
    } else {
        perror("Index out of bound of tiny Vector!\n");
        exit(EXIT_FAILURE);
    }
}