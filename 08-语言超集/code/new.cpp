#include <iostream>
#include <iomanip>

using namespace std;

class Person{
private:
    /* data */
public:
    Person(){
        cout << "构造函数调用!" << endl;
    }
    ~Person(){
        cout << "析构函数调用!" << endl;
    }
};





int main(){
    Person p;
    return 0;
}