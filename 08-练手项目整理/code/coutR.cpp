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
    private:
        string name;
        unsigned char sex;
        unsigned short age;
    public:
        Person(){};
        Person(string name, unsigned char sex, unsigned char age) : name(name), sex(sex), age(age){};

    public:
        ostream& operator<<(ostream &os){
            os << "{Person: "
               << this->name
               << ", "
               << (this->sex ? "男" : "女")
               << ", "
               << this->age << "}";
            return os;
        }
    public:
        ~Person(){};
};

int main(){

    // 匿名类也可以调用方法
    Person("路人甲", 1, 18) << cout << endl;

    
    return 0;
}