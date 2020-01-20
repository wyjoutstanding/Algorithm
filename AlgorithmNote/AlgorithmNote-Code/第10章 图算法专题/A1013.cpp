/*
 * @Author: wuyangjun
 * @Date: 2019-08-14 10:58:24
 * @LastEditTime: 2019-08-14 11:51:40
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
vector<int> Adj[maxn]; // 邻接表，从1开始
bool vis[maxn] = {false}; // 标记结点是否被访问
int N; // 结点个数
void dfs(int v) {
    vis[v] = true;
    for(auto p : Adj[v]) {
        if(!vis[p]) dfs(p);
    }
}
int dfsTrave(int delv) {
    int cnt = 0;
    // fill(vis, vis + N + 1, false); // 初始化，下标从1开始存！！！
    fill(vis, vis + maxn, false); // 初始化，下标从1开始存！！！
    vis[delv] = true; // 删除delv点
    for(int v = 1; v <= N; v ++) { // 遍历所有结点
        if(!vis[v]) {
            cnt ++; // 无向图连通块个数
            dfs(v);
        }
    }
    return cnt;
}
void readData() {
    int m, k;
    scanf("%d %d %d", &N, &m, &k);
    int a, b;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &a, &b);
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }
    int v;
    for(int i = 0; i < k; i ++) {
        scanf("%d", &v);
        printf("%d\n", dfsTrave(v) - 1);
    }
}
int main() {
    readData();
    return 0;
}