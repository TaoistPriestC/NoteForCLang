#include "allstl.h"
#include "contact.h"
using namespace std;

bool isChange;
AddressBook adbs;

void menu(){
    printf("1.显示联系人\n");
    printf("2.添加联系人\n");
    printf("3.删除联系人\n");
    printf("4.查找联系人\n");
    printf("5.修改联系人\n");
    printf("6.清空通讯录\n");
    printf("0.退出通讯录\n");
}

void header(){
    printf("%-8s\t\t", "姓名");
    printf("%-12s\t\t", "电话");
    printf("%-12s\t\t", "地址");
    printf("%-4s\t\t", "性别");
    printf("%-3s\t\n", "年龄");
}

void cls(){
    system("read -p '按任意键继续...' var");
    system("clear");
}



// 输入一个联系人
void inputContact(Person *ps){
    cout << ("姓名:");
    cin >> ps->name;
    cout << ("电话:");
    cin >> ps->tel;
    cout << ("地址:");
    cin >> ps->addr;

    cout << ("性别:\n");
    cout << ("-----[0]--->女") << endl;
    cout << ("-----[1]--->男") << endl;
    while (1){
        scanf("%hhd", &ps->sex);
        if(ps->sex == 0 || ps->sex == 1){
            break;
        }
        printf(INPUT_WRONG);
    }
    cout << ("年龄:");
    scanf("%hhd", &ps->age);
}

// 输入一个联系人
void outputContact(Person *ps){
    printf("%-8s\t\t", ps->name.c_str());
    printf("%-12s\t\t", ps->tel.c_str());
    printf("%-12s\t\t", ps->addr.c_str());
    printf("%-4s\t\t", ps->sex ? "男" : "女");
    printf("%-3d\t\n", ps->age);
}



// 打开通讯录
File openFile(const char *filename, const char * mode){
    File fp = fopen(filename, mode);
    if(fp == nullptr){
        exit(EXIT_FAILURE);
    }
    return fp;
}

// 关闭通讯录
void closeFile(File fp){
    if(fp != nullptr){
        fclose(fp);
    }
}



void showContact(){
    if (adbs.size == 0){
        printf(AD_BOOK_EMPTY);
    }else{
        header();
        for (int i = 0; i < adbs.size; i++){
            outputContact(&adbs.contactList[i]);
        }
    }
    cls();
}


ssize_t findContact(){
    string pat;
    cout << "目标联系人姓名:";
    cin >> pat;
    for (int i = 0; i < adbs.size; i++){
        if (adbs.contactList[i].name == pat){
            return i;
        }
    }
    return -1;
}



void addContact(){
    if(adbs.size == MAXN){
        printf(AD_BOOK_FULL);
    }else{
        inputContact(&adbs.contactList[adbs.size++]);
        isChange = true;
    }
    cls();
}


void subContact(){
    ssize_t idx = findContact();
    if (idx < 0){
        printf(PERSON_NO_FOUND);
    }else{
        for (int i = idx; i < adbs.size - 1; i++){
            adbs.contactList[i] = adbs.contactList[i + 1];
        }
        adbs.size--;
        isChange = true;
    }
    cls();
}


void retrieveContact(){
    ssize_t idx = findContact();
    if (idx < 0){
        printf(PERSON_NO_FOUND);
    }else{
        header();
        outputContact(&adbs.contactList[idx]);
    }
    cls();
}

void modifyContact(){
    ssize_t idx = findContact();
    if (idx < 0){
        printf(PERSON_NO_FOUND);
    }else{
        inputContact(&adbs.contactList[idx]);
        isChange = true;
    }
    cls();
}

void clearContact(){
    printf(AD_BOOK_CLEARED);
    adbs.size = 0;
    isChange = true;
    cls();
}

void exitContact(){
    printf(WELCOME_NEXT_TIME);
    if(isChange){
        File fp = openFile("database", "w+");
        fprintf(fp, "%ld\n", adbs.size);
        for (int i = 0; i < adbs.size; i++){
            fprintf(fp, "%s %s %s %hhd %hhd\n",
                    adbs.contactList[i].name.c_str(),
                    adbs.contactList[i].tel.c_str(),
                    adbs.contactList[i].addr.c_str(),
                    adbs.contactList[i].sex,
                    adbs.contactList[i].age);
        }
        closeFile(fp);
    }
    cls();
    exit(EXIT_SUCCESS);
}


void initContact(){
    File fp = openFile("database", "r+");
    fscanf(fp, "%ld\n", &adbs.size);
    for (int i = 0; i < adbs.size; i++){
        adbs.contactList[i].name.resize(20);
        adbs.contactList[i].tel.resize(20);
        adbs.contactList[i].addr.resize(20);
        fscanf(fp, "%s %s %s %hhd %hhd\n",
               &adbs.contactList[i].name[0],
               &adbs.contactList[i].tel[0],
               &adbs.contactList[i].addr[0],
               &adbs.contactList[i].sex,
               &adbs.contactList[i].age);
    }
    closeFile(fp);
}
