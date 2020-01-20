/*
 * @Author: wuyangjun
 * @Date: 2019-08-21 19:14:56
 * @LastEditTime: 2019-08-21 21:07:06
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 510, INF = 0x3fffffff;
struct GNode {
    int v, d;
    GNode(int _v, int _d) : v(_v), d(_d) {}
};
vector<GNode> Adj[MAXN]; // 邻接表
int d[MAXN], weight[MAXN] = {0}; // 最短距离, 点权
bool vis[MAXN]; // 记录访问
vector<int> pre[MAXN]; // 前缀
int Cmax, N, Sp, M;
vector<int> tmpPath, ansPath; // 临时路径， 结果路径
int minWeight = INF; // 最小花费权值
int sendNum = INF, remainNum = INF; //运送， 返回数量
// 获取所有最短路径
void dijkstra(int s) {
    // initialization
    fill(vis, vis + MAXN, false);
    fill(d, d + MAXN, INF);
    d[s] = 0;
    // N + 1 iteratation
    for(int i = 0; i <= N; i ++) {
        // find minimal vertex
        int u, MIN = INF;
        for(int v = 0; v <= N; v ++) {
            if(!vis[v] && d[v] < MIN) {
                u = v;
                MIN = d[v];
            }
        }
        // visit vertex
        vis[u] = true;
        // update relate edge with u
        for(auto p : Adj[u]) {
            if(!vis[p.v]) {
                if(p.d + d[u] < d[p.v]) {
                    d[p.v] = p.d + d[u];
                    pre[p.v].clear();
                    pre[p.v].push_back(u);
                }
                else if(p.d + d[u] == d[p.v]) {
                    pre[p.v].push_back(u);
                }
            }
        }
    }
}
// 遍历每条最短路径，选出符合条件的路径
void dfs(int v) {
    if(v == 0) { // 起点
        tmpPath.push_back(v);
        int send = 0, remain = 0, tmp;
        // 模拟整理：从末尾开始，排除起始点
        for(int i = tmpPath.size() - 2; i >= 0; i --) { 
            int p = tmpPath[i];
            // printf("==p %d %d %d\n", p, send, remain);
            tmp = weight[p] - Cmax / 2; 
            if(tmp >= 0) remain += tmp; // 剩余
            else { // 无剩余
                if(remain >= abs(tmp)) remain -= abs(tmp); // 路上补给足够
                else { // 路上补给不足，从起点取
                    send += abs(tmp) - remain;
                    remain = 0;
                }
            } 
        }
        // 更新:送的数量小者优先; 送相同，返回小者优先
        if(send < sendNum || (send == sendNum && remain < remainNum)) { 
            sendNum = send;
            remainNum = remain;
            ansPath = tmpPath;
        }
        tmpPath.pop_back(); // 弹出该顶点
        return; // 必须返回
    }
    tmpPath.push_back(v); 
    for(auto p : pre[v]) { // 遍历每个前缀
        dfs(p);
    }
    tmpPath.pop_back();
}
void readData() {
    scanf("%d %d %d %d", &Cmax, &N, &Sp, &M);
    for(int i = 1; i <= N; i ++) scanf("%d", &weight[i]); // 从1开始
    int a, b, t;
    for(int i = 0; i < M; i ++) {
        scanf("%d %d %d", &a, &b, &t);
        Adj[a].push_back(GNode(b, t)); // 无向图
        Adj[b].push_back(GNode(a, t));
    }
}
void showResult() {
    printf("%d ", sendNum);
    for(int i = ansPath.size() - 1; i >= 0; i --) {
        printf("%d%s", ansPath[i], i == 0 ? " " : "->");
    }
    printf("%d\n", remainNum);
}
int main() {
    readData();
    dijkstra(0);
    dfs(Sp); 
    showResult();
    return 0;
}