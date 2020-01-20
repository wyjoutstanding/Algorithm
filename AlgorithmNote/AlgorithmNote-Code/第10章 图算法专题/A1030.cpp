/*
 * @Author: wuyangjun
 * @Date: 2019-08-15 20:00:55
 * @LastEditTime: 2019-08-15 20:50:23
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 510, INF = 0x3fffffff;
struct GNode {
    int v, w, c; // 点， 距离， 花费
    GNode(int _v, int _w, int _c) : v(_v), w(_w), c(_c) {}
};
vector<GNode> Adj[MAXN];
int vis[MAXN], d[MAXN], c[MAXN] = {0}, pre[MAXN]; // 记录访问， 最小距离， 最小花费， 前驱
int N, M, S, D;
vector<int> ans; // 存放最短路径
void Dijkstra(int s) {
    // 初始化
    fill(vis, vis + MAXN, false);
    fill(d, d + MAXN, INF);
    d[s] = 0;
    for(int i = 0; i < MAXN; i ++) pre[i] = i;
    // N轮迭代
    for(int i = 0; i < N; i ++) {
        // 选最小
        int u = -1, MIN = INF;
        for(int v = 0; v < N; v ++) {
            if(!vis[v] && MIN > d[v]) {
                MIN = d[v];
                u = v;
            }
        }
        vis[u] = true; // 标记u
        // 优化
        for(auto p : Adj[u]) {
            if(!vis[p.v]) {
                if(d[u] + p.w < d[p.v]) {
                    d[p.v] = d[u] + p.w;
                    pre[p.v] = u;
                    c[p.v] = c[u] + p.c;
                }
                else if(d[u] + p.w == d[p.v] && c[u] + p.c < c[p.v]) {
                    pre[p.v] = u;
                    c[p.v] = c[u] + p.c;
                }
            }
        }
    }
}
// 回溯找到最短路径
void dfs(int v) {
    if(v == S) {
        ans.push_back(v);
        return;
    }
    dfs(pre[v]);
    ans.push_back(v);
}
// 读入数据并以邻接表建立无向带权图
void createGraph() {
    scanf("%d %d %d %d", &N, &M, &S, &D);
    int a, b, d, c;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d %d %d", &a, &b, &d, &c);
        Adj[a].push_back(GNode(b, d, c));
        Adj[b].push_back(GNode(a, d, c));
    }
}
// 展示结果
void showResult() {
    for(auto p : ans) printf("%d ", p);
    printf("%d %d\n", d[D], c[D]);
}
int main() {
    createGraph();
    Dijkstra(S);
    dfs(D);
    showResult();
    return 0;
}