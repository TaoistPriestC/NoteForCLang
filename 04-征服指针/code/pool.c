#include <stdio.h>
#include <stdlib.h>


#define MAXN 256

typedef struct Person{
    char name[32];
    unsigned char age;
} Person;

typedef Person *PersonPtr;


PersonPtr pools[MAXN];

PersonPtr getPerson(){
    // 如果结构体池尚有对象则将对象返回,如果结构体池没有对象原地创建
    for (int i = 0; i < MAXN; i++){
        if (pools[i] != NULL){
            PersonPtr ptr = pools[i];
            pools[i] = NULL;
            return ptr;
        }
    }
    return (PersonPtr)malloc(sizeof(Person));
}

PersonPtr retPerson(PersonPtr p){
    // 如果结构体池仍有空间则将p归还放入池中,如果结构体池已满直接释放p
    for (int i = 0; i < MAXN; i++){
        if (pools[i] == NULL){
            return (pools[i] = p);
        }
    }
    free(p);
    return NULL;
}


int main(){
    /**
     * @brief 
     * 建议修改一下MAXN然后写几个测试用例便可看出来
     */
    return 0;
}