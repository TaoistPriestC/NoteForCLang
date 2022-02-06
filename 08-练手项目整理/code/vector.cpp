#include "vector.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::ostream;
using std::istream;

using std::endl;
using std::sin;
using std::cos;
using std::sqrt;
using std::atan;
using std::atan2;
using std::fixed;
using std::setprecision;

namespace VECTOR{
    // 转化所需的常量
    const double Rad_TO_DEG = 45.0f / atan(1.0);

    // 基本私有方法
    void Vector::set_mag() { mag = sqrt(x * x + y * y); }
    void Vector::set_ang() { ang = (x == 0.0f && y == 0.0f) ? 0.0f : atan2(y, x); }
    void Vector::set_x() { x = mag * cos(ang); }
    void Vector::set_y() { y = mag * sin(ang); }

    // 构造函数
    Vector::Vector(){
        x = y = mag = ang = 0.0f;
        mode = RECT;
    }
    Vector::Vector(double n1, double n2, Mode form){
        this->mode = form;
        switch (form){
            case RECT:
                x = n1;
                y = n2;
                set_mag();
                set_ang();
                break;
            case POL:
                mag = n1;
                ang = n2;
                set_x();
                set_y();
            default:
                cout << "Incorrect Mode,the 3rd argument, to Vector()!" << endl;
                cout << "Vector set to zero!" << endl;
                x = y = mag = ang = 0.0f;
                mode = RECT;
                break;
        }
    }

    // 其它常用的公共函数
    void Vector::reset(double n1, double n2, Mode form){
        mode = form;
        switch (form){
            case RECT:
                x = n1;
                y = n2;
                set_mag();
                set_ang();
                break;
            case POL:
                mag = n1;
                ang = n2;
                set_x();
                set_y();
            default:
                cout << "Incorrect Mode,the 3rd argument, to Vector()!" << endl;
                cout << "Vector set to zero!" << endl;
                x = y = mag = ang = 0.0f;
                mode = RECT;
                break;
        }
    }

    // 修改模式
    void Vector::polar_mode() { mode = Vector::POL; }
    void Vector::rect_mode() { mode = Vector::RECT; }


    // 下面涉及了大量的重载运算符
    
    // 向量加减法
    Vector Vector::operator+(const Vector &other) const { return Vector(x + other.x, y + other.y); }
    Vector Vector::operator-(const Vector &other) const { return Vector(x - other.x, y - other.y); }
    
    // 向量正负号
    Vector Vector::operator+() const { return Vector(+x, +y); }
    Vector Vector::operator-() const { return Vector(-x, -y); }

    // 向量与常数的运算, 模仿numpy广播机制
    Vector Vector::operator+(double n) const { return Vector(n + x, n + y); }
    Vector Vector::operator-(double n) const { return Vector(n - x, n - y); }
    Vector Vector::operator*(double n) const { return Vector(n * x, n * y); }

    // 向量之间的运算
    Vector operator+(double n, const Vector &other) { return other + n; }
    Vector operator-(double n, const Vector &other) { return other - n; }
    Vector operator*(double n, const Vector &other) { return other * n; }

    // 输入与输出
    istream &operator>>(istream &is, Vector &vec){
        while(1){
            int mode, ok = 0;
            cout << "Mode (press 0/1 to choose RECT/POL):";
            is >> mode;
            vec.mode = mode ? vec.POL : vec.RECT;
            switch (mode){
                case 0:
                    cout << "x = ";
                    is >> vec.x;
                    cout << "y = ";
                    is >> vec.y;
                    vec.set_mag();
                    vec.set_ang();
                    ok = 1;
                    break;
                case 1:
                    cout << "mag = ";
                    is >> vec.mag;
                    cout << "ang = ";
                    is >> vec.ang;
                    vec.set_x();
                    vec.set_y();
                    ok = 1;
                    break;
                default:
                    cout << "Incorrect Mode! Input again please!" << endl;
                    break;
            }
            if(ok) break;
        }
        return is;
    }
    ostream &operator<<(ostream &os, Vector &vec){
        switch(vec.mode){
            case Vector::RECT :
                os << "(  x ,  y  ) = "
                   << fixed << setprecision(2)
                   << "(" 
                   << vec.x << ", " 
                   << vec.y << ")";
                break;
            case Vector::POL :
                os << "( mag, ang ) = "
                   << fixed << setprecision(2)
                   << "(" 
                   << vec.mag << ", " 
                   << vec.ang << ")";
                break;
            default:
                os << "Vector object mode is invalid!" << endl;
        }
        return os;
    }
}

int main(){
    VECTOR::Vector v;
    cin >> v;
    v.polar_mode();
    cout << v << endl;
    v.rect_mode();
    cout << v << endl;
}