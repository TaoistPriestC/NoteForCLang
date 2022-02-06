#include <stdio.h>
#include <string.h>

#define MAXN 50000

int parent[MAXN];
int nodeNum[MAXN];
int dist[MAXN];
int n, a, b, s;

// 本例逻辑练习是对北大POJ1988题目的解答
void init(){
    // 使用nodeNum记录木块数量
    for (int i = 0; i < MAXN; i++){
        parent[i] = i;
        nodeNum[i] = 1;
        dist[i] = 0;
    }
}

int find(int x){
    if (x != parent[x]){
        int t = parent[x];
        parent[x] = find(parent[x]);
        dist[x] += dist[t];
        return parent[x];
    }
    return x;
}

void merge(int a,int b){
    a = find(a);
    b = find(b);
    if (a != b){
        parent[b] = a;
        dist[b] += nodeNum[a];
        nodeNum[a] += nodeNum[b];
    }
}


int main(){
    char str[3];
    while (scanf("%d", &n) != EOF){
        init();
        for (int i = 0; i < n; i++){
            scanf("%s", str);
            if (str[0] == 'M'){
                scanf("%d%d", &a, &b);
                merge(a, b);
            }else{
                scanf("%d", &s);
                printf("%d\n", nodeNum[find(s)] - dist[s] - 1);
            }
        }
    }
    return 0;
}