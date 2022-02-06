#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>
#include <iomanip>


namespace INTEGER{
    class Integer{
        private:
            long int num;
        public:
            Integer();
            Integer(long int);

        public:
            // 前项自增与后项自增
            Integer &operator++();
            Integer operator++(int);

            //友元声明
            friend std::ostream &operator<<(std::ostream &os, Integer x);
            friend std::istream &operator>>(std::istream &is, Integer &x);

        public:
            ~Integer() {}
    };
}

#endif