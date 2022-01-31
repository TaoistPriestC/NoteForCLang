#include <iostream>
#include <iomanip>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;


class Person{
    friend ostream &operator<<(ostream &os, Person &p);

    private:
        string name;
        unsigned char sex;
        unsigned short age;
    public:
        Person(){};
        Person(string name, unsigned char sex, unsigned char age) : name(name), sex(sex), age(age){};        

    public:
        ~Person(){};
};

// 匿名类一旦创建运行构造函数之后便立即释放, 是没有引用的
ostream &operator<<(ostream &os, Person &p){
    os << "{Person: "
       << (p.name)
       << ", "
       << (p.sex ? "男" : "女")
       << ", "
       << (p.age) << "}";
    return os;
}

int main(){
    Person p("路人甲", 1, 18);
    /**
     * @brief 
     * 由于匿名类不具有引用,所以下面这句代码会报错
     * cout << Person("路人甲", 1, 18) << endl;
     */

    cout << p << endl;
    return 0;
}