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

// ������һ���������й��캯��֮��������ͷ�, ��û�����õ�
ostream &operator<<(ostream &os, Person &p){
    os << "{Person: "
       << (p.name)
       << ", "
       << (p.sex ? "��" : "Ů")
       << ", "
       << (p.age) << "}";
    return os;
}

int main(){
    Person p("·�˼�", 1, 18);
    /**
     * @brief 
     * ���������಻��������,��������������ᱨ��
     * cout << Person("·�˼�", 1, 18) << endl;
     */

    cout << p << endl;
    return 0;
}