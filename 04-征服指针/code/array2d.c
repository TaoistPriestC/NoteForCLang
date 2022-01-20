#include<stdio.h>
#include <stdlib.h>

// 内存不连续的二维动态数组
// 不过这种不连续对于使用方括号运算符来说是透明的
int** createArray2D_discrate(int rows,int cols){
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++){
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

// 内存连续的二维动态数组
// 先对二级指针首元素赋值大块区域,再分段的拆给余下二级指针
int** createArray2D_continuous(int rows,int cols){
    int **matrix = (int **)malloc(rows * sizeof(int *));
    *matrix = (int *)malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++){
        matrix[i] = matrix[0] + i * cols;
    }
    return matrix;
}

void initArray2D(int **mat, int rows, int cols, int val){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            mat[i][j] = val;
        }
    }
}

void printArray2D(int **mat, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void test(int **mat, int rows, int cols, int val){
    initArray2D(mat, rows, cols, val);
    printArray2D(mat, rows, cols);
}



int main(){
    int rows = 3, cols = 3, val = 6;
    int **mat1 = createArray2D_discrate(rows, cols);
    int **mat2 = createArray2D_continuous(rows, cols);
    test(mat1, rows, cols, val);
    test(mat2, rows, cols, val);
    
    return 0;
}