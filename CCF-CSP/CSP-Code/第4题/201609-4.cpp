/*
 * @Author: wuyangjun
 * @Date: 2019-09-16 19:53:22
 * @LastEditTime: 2019-09-16 20:27:31
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010, INF = 0x3fffffff;
struct GNode { // 邻接表节点
    int v, d;
};
struct HeapNode { // 存储源点到v的距离d，为优先队列优化准备
    int v, d;
    friend bool operator < (const HeapNode& a, const HeapNode& b) {return a.d > b.d;}
};
vector<GNode> adj[maxn];
int vis[maxn] = {false}, d[maxn] = {0}, cost[maxn] = {0}; // 访问，起点到当前点距离，到当前点的最短边
int ans = 0; // 存储结果
priority_queue<HeapNode> q;
void dijkstra(int s) {
    fill(d + 2, d + maxn, INF);
    fill(cost + 2, cost + maxn, INF);
    q.push(HeapNode{s, 0}); // 源点入队
    while(!q.empty()) {
        HeapNode cur = q.top(); q.pop();
        if(vis[cur.v]) continue; // 跳过已经访问过的
        vis[cur.v] = true; // 访问
        ans += cost[cur.v]; // 累加边权
        for(auto& p : adj[cur.v]) {
            if(!vis[p.v]) {
                if(d[p.v] > d[cur.v] + p.d || (d[p.v] == d[cur.v] + p.d && p.d < cost[p.v])) { // 最短路径/最短路相同边更短
                    d[p.v] = d[cur.v] + p.d;
                    cost[p.v] = p.d;
                    q.push(HeapNode{p.v, d[p.v]}); // 发生改变才入队
                }
            }
        }
    }
    printf("%d\n", ans);
}
int main() {
    int n, m, a, b, c;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i ++) {
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back(GNode{b, c});
        adj[b].push_back(GNode{a, c});
    }
    dijkstra(1);
    return 0;
}