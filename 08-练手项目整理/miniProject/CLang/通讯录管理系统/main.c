#include <stdio.h>
#include <string.h>
#include "infoio.h"
#include "contact.h"

void menu(){
    printf("=======================\n");
    printf("===== 1.显示联系人 =====\n");
    printf("===== 2.添加联系人 =====\n");
    printf("===== 3.删除联系人 =====\n");
    printf("===== 4.查找联系人 =====\n");
    printf("===== 5.修改联系人 =====\n");
    printf("===== 6.清空通讯录 =====\n");
    printf("===== 0.退出通讯录 =====\n");
    printf("=======================\n");
}


int main(){    
    int select = 0;
    initContact();
    while(1){
        menu();
        scanf("%d", &select);
        switch (select){
            case 1://显示
                showContact();
                break;
            case 2://添加
                addContact();
                break;
            case 3://删除
                subContact();
                break;
            case 4://查找
                retrieveContact();
                break;
            case 5://修改
                modifyContact();
                break;
            case 6://清空
                clearContact();
                break;
            case 0://退出
                exitContact();
            default:
                break;
        }
    }
    return 0;
}