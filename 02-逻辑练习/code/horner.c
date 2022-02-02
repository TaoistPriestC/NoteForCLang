#include <stdio.h>


#define  MAXN 5000

int x, n, m, c, e;
int poly, coef[MAXN];

// 使用霍纳算法,或说秦九韶算法计算多项式
// 测试 F(X) = 4X^4 + 8X^3 + X + 2 这条多项式
int main(){
    // 多项式次数N、项数m
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++){
        scanf("%d %d", &c, &e);
        coef[e] = c;
    }

    poly = 0;
    scanf("%d", &x);
    for (int i = n; i >= 0; i--){
        poly = x * poly + coef[i];
    }
    printf("%d\n", poly);
    return 0;
}