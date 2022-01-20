#include<stdio.h>
typedef int (*operation)(int, int);


operation ops[128];

int add(int a,int b){
    return a + b;
}

int sub(int a,int b){
    return a - b;
}

void initOpsArray(){
    ops['+'] = add;
    ops['-'] = sub;
}

int calc(char op,int a,int b){
    operation o = ops[op];
    return o(a, b);
}


int main(){
    initOpsArray();
    printf("%d\n",calc('+', 4, 5));
    printf("%d\n",calc('-', 5, 4));
    return 0;
}