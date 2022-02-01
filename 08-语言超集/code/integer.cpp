#include "integer.h"
#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

namespace INTEGER{
    Integer::Integer(){
        this->num = 0;
    }

    Integer::Integer(long int num){
        this->num = num;
    }

    Integer &Integer::operator++(){
        this->num++;
        return *this;
    }

    Integer Integer::operator++(int){
        Integer ret = *this;
        this->num++;
        return ret;
    }


    // 下面的输入与输出是友元函数
    // 类内重载运算符其实会有一个默认的指向对象自身的参数
    // 以下两个函数必须要在类外实现, 故不必添加Integer类命名空间
    ostream &operator<<(ostream &os, Integer x){
        os << x.num;
        return os;
    }
    istream &operator>>(istream &is, Integer &x){
        is >> x.num;
        return is;
    }
}

class Base{
    public:
        int a;
    protected:
        int b;
    private:
        int c;
};

class Son: public Base{
    private:
        int d;
};

int main(){
    INTEGER::Integer x = 3;
    cout << ++x << ", " << x << endl;
    cout << x++ << ", " << x << endl;
    return 0;
}