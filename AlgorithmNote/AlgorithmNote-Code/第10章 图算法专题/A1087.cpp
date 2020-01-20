/*
 * @Author: wuyangjun
 * @Date: 2019-08-22 10:12:17
 * @LastEditTime: 2019-08-22 10:52:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 220, INF = 0x3fffffff;
struct GNode {
    int v, d;
    GNode(int _v, int _d) : v(_v), d(_d) {}
};
vector<GNode> Adj[maxn];
bool vis[maxn];
int d[maxn], weight[maxn] = {0}; // 最短距离， 点权
vector<int> pre[maxn], tmpPath, ansPath; // 前驱、临时最短路径、结果最短路径
int ansNum = 0, ansHp = -1; // 最短路径条数、最大快乐
int N, K, S, D; // 顶点个数、边数、起点、终点
map<string, int> sti; // city -> id
map<int, string> its; // id -> city
int vNum = 0; // 顶点编号
// 字符串 -> 编号
int change(string s) {
    if(sti.count(s) == 0) {
        sti[s] = vNum;
        its[vNum] = s;
        vNum ++;
    }
    return sti[s];
}
// 找出所有点的前驱
void dijkstra(int s) {
    // 初始化
    fill(vis, vis + maxn, false);
    fill(d, d + maxn, INF);
    d[s] = 0;
    // N轮迭代
    for(int i = 0; i < N; i ++) {
        // 最小点
        int MIN = INF, u = -1;
        for(int v = 0; v < N; v ++) {
            if(!vis[v] && d[v] < MIN) {
                u = v;
                MIN = d[v];
            }
        }
        // 访问
        vis[u] = true;
        // 更新
        for(auto p : Adj[u]) {
            if(!vis[p.v]) {
                if(d[p.v] > d[u] + p.d) {
                    d[p.v] = d[u] + p.d;
                    pre[p.v].clear();
                    pre[p.v].push_back(u);
                }
                else if(d[p.v] == d[u] + p.d) pre[p.v].push_back(u);
            }
        }
    }
}
// 遍历所有最短路，统计最短路条数、最优路径
void dfs(int v) {
    if(v == S) {
        ansNum ++; // 统计最短路径条数
        tmpPath.push_back(v);
        int sumHp = 0; // 总快乐
        for(auto p : tmpPath) {
            sumHp += weight[p];
        }
        if(sumHp > ansHp) { // 总快乐大者优先
            ansHp = sumHp;
            ansPath = tmpPath;
        }
        else if(sumHp == ansHp && tmpPath.size() < ansPath.size()) { // 总快乐同，平均快乐大者优先
            ansPath = tmpPath;
        }
        tmpPath.pop_back();
        return;
    }
    tmpPath.push_back(v);
    for(auto p : pre[v]) dfs(p);
    tmpPath.pop_back();
}
void readData() {
    string city;
    cin >>N >>K >>city;
    S = change(city); // 起点
    int id, w;
    for(int i = 0; i < N - 1; i ++) {
        cin >>city >>w;
        id = change(city);
        weight[id] = w;
    }
    string a, b;
    int u, v, d;
    for(int i = 0; i < K; i ++) {
        cin >>a >>b >>d;
        u = change(a);
        v = change(b);
        Adj[u].push_back(GNode(v, d));
        Adj[v].push_back(GNode(u, d));
    }
    D = change("ROM"); // 终点
}
void showResult() {
    printf("%d %d %d %d\n", ansNum, d[D], ansHp, (int)ansHp / (ansPath.size() - 1));
    for(int i = ansPath.size() - 1; i >= 0; i --) {
        printf("%s%s", its[ansPath[i]].c_str(), i == 0 ? "\n" : "->");
    }
}
int main() {
    readData();
    dijkstra(S);
    dfs(D);
    showResult();
    return 0;
}