#pragma once
#include "contact.h"


// 函数声明
void header();
void cls();

// 输入与输出一个联系人的信息
void inputContact(Person *ps);
void outputContact(Person *ps);



// 封装的文件操作函数
File openFile(const char *filename, const char *mode);
void closeFile(File fp);