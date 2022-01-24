#include<stdio.h>
#include<iostream>

using namespace std;

template<typename type>
void Swap(type &a, type &b){
    type t = a;
    a = b;
    b = t;
}

int main(){
    int a = 3;
    int b = 5;

    decltype((a)) ra = a;
    decltype((b)) rb = b;

    swap<int>(a, b);
    printf("a = %d, b = %d\n", a, b);

    Swap<int>(a, b);
    printf("a = %d, b = %d\n", a, b);

    return 0;
}