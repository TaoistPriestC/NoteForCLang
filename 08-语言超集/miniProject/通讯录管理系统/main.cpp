#include "allstl.h"
#include "contact.h"

using namespace std;


int main(){    
    int select = 0;
    initContact();
    while(1){
        menu();
        cin >> select;
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