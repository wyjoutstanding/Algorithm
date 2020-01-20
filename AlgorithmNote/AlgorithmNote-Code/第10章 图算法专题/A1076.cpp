/*
 * @Author: wuyangjun
 * @Date: 2019-08-14 23:29:09
 * @LastEditTime: 2019-08-14 23:45:56
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
vector<int> Adj[maxn];
int layer[maxn]; // 存放每个结点层号
bool vis[maxn];
int N, L;
int bfs(int v) {
    int maxNum = 0; // 最大转发数
    queue<int> q;
    q.push(v);
    vis[v] = true; // 入队立刻标记已入栈
    layer[v] = 0; // 层号
    while(!q.empty()) {
        int now = q.front();
        q.pop();
        if(layer[now] <= L) { // L层以内
            maxNum ++;
        }
        else break;
        for(auto p : Adj[now]) { // 邻结点
            if(!vis[p]) { // 尚未入栈
                q.push(p);
                vis[p] = true;
                layer[p] = layer[now] + 1; // 层号加1
            }
        }
    }
    return maxNum - 1;
}
void createGraph() {
    scanf("%d %d", &N, &L);
    int n, t;
    for(int i = 1; i <= N; i ++) {
        scanf("%d", &n);
        for(int j = 0; j < n; j ++) {
            scanf("%d", &t);
            Adj[t].push_back(i); // 有向图
        }
    }
    //  K个查询
    int K, query;
    scanf("%d", &K);
    for(int i = 0; i < K; i ++) {
        scanf("%d", &query);
        fill(vis, vis + maxn, false); // 初始化
        printf("%d\n", bfs(query));
    }
}
int main() {
    createGraph();
    return 0;
}