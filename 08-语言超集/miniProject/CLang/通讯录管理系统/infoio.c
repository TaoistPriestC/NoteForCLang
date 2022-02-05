#include <stdio.h>
#include <stdlib.h>

#include "infoio.h"
#include "config.h"
#include "contact.h"


void header(){
    printf("%-12s\t\t", "姓名");
    printf("%-12s\t\t", "电话");
    printf("%-12s\t\t", "地址");
    printf("%-4s\t\t", "性别");
    printf("%-4s\t\n", "年龄");
}

void cls(){
    system("read -p '按任意键继续...' var");
    system("clear");
}


// 输入一个联系人
void inputContact(Person *ps){
    printf("姓名:");
    scanf("%s", &ps->name[0]);
    printf("电话:");
    scanf("%s", &ps->tel[0]);
    printf("地址:");
    scanf("%s", &ps->addr[0]);

    printf("性别:\n");
    printf("-----[0]--->女\n");
    printf("-----[1]--->男\n");
    while (1){
        scanf("%hhd", &ps->sex);
        if(ps->sex == 0 || ps->sex == 1){
            break;
        }
        printf(INPUT_WRONG);
    }
    printf("年龄:");
    scanf("%hhd", &ps->age);
}


// 输出一个联系人
void outputContact(Person *ps){
    printf("%-12s\t\t", ps->name);
    printf("%-12s\t\t", ps->tel);
    printf("%-12s\t\t", ps->addr);
    printf("%-4s\t\t", ps->sex ? "男" : "女");
    printf("%-4d\t\n", ps->age);
}




/** 文件开关封装:打开
 * @brief 
 * 
 */
File openFile(const char *filename, const char * mode){
    File fp = fopen(filename, mode);
    if(fp == NULL){
        exit(EXIT_FAILURE);
    }
    return fp;
}


/** 文件开关封装:关闭
 * @brief 
 * 
 */
void closeFile(File fp){
    if(fp != NULL){
        fclose(fp);
    }
}