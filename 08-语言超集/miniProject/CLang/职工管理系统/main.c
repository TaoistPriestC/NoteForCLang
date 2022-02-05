#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "infoio.h"
#include "worker.h"


void menu(){
    printf("\t=========================\n");
    printf("\t===== 1.显示职工信息 =====\n");
    printf("\t===== 2.添加职工信息 =====\n");
    printf("\t===== 3.删除职工信息 =====\n");
    printf("\t===== 4.查找职工信息 =====\n");
    printf("\t===== 5.修改职工信息 =====\n");
    printf("\t===== 6.清空职工信息 =====\n");
    printf("\t===== 7.按照工号排序 =====\n");
    printf("\t===== 0.退出管理系统 =====\n");
    printf("\t=========================\n");
}


int op = 0;
int main(){
    initWorkBook();
    while (1){
        menu();
        scanf("%d", &op);
        switch(op){
            case 1:
                outputWorkers();
                break;
            case 2:
                inputWorkers();
                break;
            case 3:
                deleteWorkers();
                break;
            case 4:
                findWorker();
                break;
            case 5:
                updateWorker();
                break;
            case 6:
                clearWorkers();
                break;
            case 7:
                sortWorkers();
                break;
            case 0:
                exitWorkBook();
                break;
            default:
                break;
        }
    }
    return 0;
}