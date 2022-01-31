#ifndef VeCTOR_H
#define VeCTOR_H

// 现在这种ifndef-define-endif模式通常使用#pragma once代替
#include <iostream>
#include <iomanip>

namespace VECTOR{
    class Vector{
        public:
            enum Mode{
                RECT,
                POL
            };
        private:
            double x;   // 横坐标
            double y;   // 纵坐标
            double mag; // 长度
            double ang; // 角度
            Mode mode;  // 模式
        private:
            void set_mag();
            void set_ang();
            void set_x();
            void set_y();
        public:
            Vector();
            Vector(double n1, double n2, Mode form = RECT);
        public:
            void reset(double n1, double n2, Mode form = RECT);
            double get_x() const { return this->x; }
            double get_y() const { return this->y; }
            double get_mag() const { return this->mag; }
            double get_ang() const { return this->ang; }
            void polar_mode();
            void rect_mode();

        public:
            Vector operator+(const Vector &other) const;
            Vector operator-(const Vector &other) const;
            Vector operator+() const;
            Vector operator-() const;

            // 实现左右两侧的广播机制
            Vector operator+(double n) const;
            Vector operator-(double n) const;
            Vector operator*(double n) const;

            // 友元声明
            friend Vector operator+(double n, const Vector &vec);
            friend Vector operator-(double n, const Vector &vec);
            friend Vector operator*(double n, const Vector &vec);

            friend std::ostream &operator<<(std::ostream &os, Vector &vec);
            friend std::istream &operator>>(std::istream &is, Vector &vec);

            // 必须注意声明与实现哪怕只有一丁点不同都将报错!
        public:
            ~Vector(){};
    };
}

#endif
