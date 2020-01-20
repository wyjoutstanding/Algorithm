/*
 * @Author: wuyangjun
 * @Date: 2019-08-15 21:02:39
 * @LastEditTime: 2019-08-15 21:36:24
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 510, INF = 0x3fffffff;
struct GNode {
    int v, d, c;
    GNode(int _v, int _d, int _c) : v(_v), d(_d), c(_c) {}
};
vector<GNode> Adj[MAXN];
int vis[MAXN], d[MAXN];
vector<int> pre[MAXN]; // 每个点的前驱序列
int N, M, S, D;
vector<int> tmpPath, ansPath; // 临时、答案最短路径
int minCost = INF; // 最小花费
void Dijkstra(int s) {
    // 初始化
    fill(vis, vis + MAXN, false);
    fill(d, d + MAXN, INF);
    d[s] = 0;
    for(int i = 0; i < N; i ++) {
        // 最小值
        int u = -1, MIN = INF;
        for(int v = 0; v < N; v ++) {
            if(!vis[v] && MIN > d[v]) {
                MIN = d[v];
                u = v;
            }
        }
        vis[u] = true; // 标记
        // 优化
        for(auto p : Adj[u]) {
            if(!vis[p.v]) {
                if(d[u] + p.d < d[p.v]) {
                    d[p.v] = d[u] + p.d;
                    pre[p.v].clear();
                    pre[p.v].push_back(u);
                }
                else if(d[u] + p.d == d[p.v]) {
                    pre[p.v].push_back(u);
                }
            }
        }
    }
}
// 遍历所有最短路径，选出花费最小的
void dfs(int v) {
    if(v == S) {
        tmpPath.push_back(v);
        // 计算花费总和
        int sumCost = 0;
        for(int i = tmpPath.size() - 1; i > 0; i --) {
            int j = tmpPath[i - 1]; // 根据下标取对应结点
            for(auto p : Adj[tmpPath[i]]) { // 找到对应边
                if(p.v == j) {
                    sumCost += p.c;
                    break;
                } 
            }
        }
        if(sumCost < minCost) { // 保存更优解
            minCost = sumCost;
            ansPath = tmpPath;
        }
        tmpPath.pop_back(); // 别漏了
        return;
    }
    tmpPath.push_back(v);
    for(auto p : pre[v]) { // 所有前驱
        dfs(p);
    }
    tmpPath.pop_back();
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
    for(int i = ansPath.size() - 1; i >= 0; i --) printf("%d ", ansPath[i]);
    printf("%d %d\n", d[D], minCost);
}
int main() {
    createGraph();
    Dijkstra(S);
    dfs(D);
    showResult();
    return 0;
}