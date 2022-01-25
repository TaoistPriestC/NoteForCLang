
#pragma once
#define MAXN 1000

typedef struct _Person{
    std::string name;
    std::string tel;
    std::string addr;
    unsigned char sex;
    unsigned char age;
} Person;


typedef struct _AddressBook{
    Person contactList[MAXN];
    size_t size;
} AddressBook;

typedef FILE *File;


// 封装的文件操作函数
File openFile(const char *filename, const char *mode);
void closeFile(File fp);




// 函数声明
void menu();
void header();
void cls();

void inputContact(Person *ps);
void ouputContact(Person *ps);

ssize_t findContact();

void showContact();
void addContact();
void subContact();
void modifyContact();
void retrieveContact();
void clearContact();
void exitContact();
void initContact();



// 与打印消息有关的配置信息
#define     INPUT_WRONG         "输入数据有误!\n"
#define     PERSON_NO_FOUND     "查无此人!\n"
#define     WELCOME_NEXT_TIME   "欢迎下次使用!\n"

#define     AD_BOOK_CLEARED     "通讯录已清空!\n"
#define     AD_BOOK_FULL        "通讯录已满, 无法继续添加!\n"
#define     AD_BOOK_EMPTY       "通讯录为空, 没有可以显示的联系人!\n"
