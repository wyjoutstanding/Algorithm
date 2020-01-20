/*
 * @Author: wuyangjun
 * @Date: 2019-08-22 12:29:44
 * @LastEditTime: 2019-08-22 12:58:55
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 510, INF = 0x3fffffff;
struct GNode {
    int v, w; // 点、边权
    GNode(int _v, int _w) : v(_v), w(_w) {}
};
vector<GNode> Adj[maxn]; // 邻接表
int N, M, C1, C2;
int teamNum[maxn]; // 点权：每个城市的救援队个数
int vis[maxn], d[maxn], team[maxn] = {0}, num[maxn] = {0}; // 访问， 最短距离， 最多队伍， 最短路径条数
set<int> pre[maxn]; // 前驱，必须用集合去重
bool bellman(int s) {
    // 初始化
    fill(d, d + maxn, INF);
    d[s] = 0;
    team[s] = teamNum[s];
    num[s] = 1;
    // N-1轮更新
    for(int i = 0; i < N - 1; i ++) {
        for(int u = 0; u < N; u ++) {
            for(auto p : Adj[u]) {
                if(d[p.v] > d[u] + p.w) {
                    d[p.v] = d[u] + p.w;
                    num[p.v] = num[u];
                    team[p.v] = team[u] + teamNum[p.v];
                    pre[p.v].clear();
                    pre[p.v].insert(u);
                }
                else if(d[p.v] == d[u] + p.w) {
                    if(team[p.v] < team[u] + teamNum[p.v]) team[p.v] = team[u] + teamNum[p.v];
                    pre[p.v].insert(u);
                    // 重新计算num
                    num[p.v] = 0;
                    for(auto k : pre[p.v]) {
                        num[p.v] += num[k];
                    }
                }
            }
        }
    }
    // 判断是否存在源点可达的负环
    for(int u = 0; u < N; u ++) {
        for(auto p : Adj[u]) {
            if(d[p.v] > d[u] + p.w) return true; // 存在源点可达负环
        }
    }
    return true;
}
void Dijkstra(int s) {
    // 初始化
    fill(vis, vis + maxn, false);
    fill(d, d + maxn, INF);
    d[s] = 0; // 起点
    team[s] = teamNum[s]; // 点权初始化
    num[s] = 1; // 个数初始化
    // N轮迭代
    for(int i = 0; i < N; i ++) { // 0~N-1个顶点，即N轮
        // 找最小值
        int u = -1, minW = INF;
        for(int v = 0; v < N; v ++) {
            if(!vis[v] && minW > d[v]) { // 未访问且距离更小
                minW = d[v];
                u = v;
            }
        }
        vis[u] = true; // 选中访问
        // 更新优化
        for(auto p : Adj[u]) {
            if(!vis[p.v] && d[p.v] > d[u] + p.w) { // 为访问且距离距离更小
                d[p.v] = d[u] + p.w;
                team[p.v] = team[u] + teamNum[p.v]; // 最大点权
                num[p.v] = num[u]; // 最短距离个数
            }
            else if(!vis[p.v] && d[p.v] == d[u] + p.w) { // 相等，取最大点权
                if(team[p.v] < team[u] + teamNum[p.v]) {
                    team[p.v] = team[u] + teamNum[p.v];
                }
                num[p.v];
                num[p.v] += num[u];
            }
        }
    }
}
void createGraph() {
    scanf("%d %d %d %d", &N, &M, &C1, &C2);
    for(int i = 0; i < N; i ++) scanf("%d", &teamNum[i]);
    int a, b, w;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d %d", &a, &b, &w);
        Adj[a].push_back(GNode(b, w));
        Adj[b].push_back(GNode(a, w));
    }
}
int main() {
    createGraph();
    // Dijkstra(C1);
    bellman(C1);
    printf("%d %d\n", num[C2], team[C2]);
    return 0;
}