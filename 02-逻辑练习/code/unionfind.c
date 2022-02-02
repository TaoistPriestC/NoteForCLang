#include <stdio.h>
#include <string.h>

#define MAXN 20000

int treehi[MAXN];
int parent[MAXN];

int find(int x){
    int xr = x;
    while(xr!=parent[xr]){
        xr = parent[xr];
    }
    return xr;
}

int merge(int x, int y){
    int xr = find(x);
    int yr = find(y);
    if (xr == yr){
        return 0;
    }else{
        if (treehi[xr] == treehi[yr]){
            parent[xr] = yr;
            treehi[yr]++;
        }else if(treehi[xr] < treehi[yr]){
            parent[xr] = yr;
        }else if(treehi[xr] > treehi[yr]){
            parent[yr] = xr;
        }
        return 1;
    }
}

int n, m, a, b;
int main(){
    // 并查集测试
    while (scanf("%d %d", &n, &m)){
        if (n == 0 && m == 0)
            break;
        memset(treehi, 0, sizeof(treehi));
        for (int i = 0; i < n; i++){
            parent[i] = i;
        }
        for (int i = 0; i < m; i++){
            scanf("%d %d", &a, &b);
            if(!merge(a, b)){
                printf("Loop detected!\n");
            }
        }
    }

    return 0;
}