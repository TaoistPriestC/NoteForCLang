#include <stdio.h>
#include <stdlib.h>

typedef struct _Vector{
    void* array;
    int each_size;
    int len;
    int cap;
    double factor;
    // 类型方法会以结构的形式打包放在一起
}Vector;


// 创建一个全局的 VectorMethods 存储 Vector 具有的方法

/**
 * @param data_size 单个元素的尺寸
 * @param len       动态数组的长度
*/
Vector* new_vector(int len, int each_size);


/**
 * @param data_size 单个元素的尺寸
 * @param len       动态数组的长度
 * @param src       需要拷贝的数组
*/
Vector* new_vector_fromArray(int len, int each_size, void *src);

/**
 * @param vec       需要释放的数组
*/
void delete_vector(Vector *vec);

/**
 * @param i         数组随机访问的下标
*/
void* vector_at(Vector *vec, int i);