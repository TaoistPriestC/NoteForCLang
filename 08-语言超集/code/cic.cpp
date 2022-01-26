#include <iostream>
#include <iomanip>

using namespace std;


class Phone{
private:
    string pName;
public:
    Phone(string pName){
        this->pName = pName;
        cout << "Phone对象已被构造!"
             << "这是" << this->pName << endl;
    }
};


class Person{
private:
    string name;
    Phone phone;
public:
    Person(string name, string phone):name(name),phone(phone){
        cout << "Person对象已被构造!"
             << "这是" << this->name << endl;
    }
};


// 初始化列表是一种语法简化机制, 没有性能差别, 
// 通常配合构造函数的隐式转化法一同使用用于简化代码!

int main(){
    Person p1("张三", "苹果手机");
    Person p2("李四", "香蕉手机");
    Person p3("王五", "柠檬手机");
    return 0;
}