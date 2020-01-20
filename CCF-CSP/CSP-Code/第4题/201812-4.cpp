/*
 * @Author: wuyangjun
 * @Date: 2019-09-08 21:03:43
 * @LastEditTime: 2019-09-08 22:28:46
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50010, INF = 0x3fffffff;
struct GNode {
    int v, d;
    GNode(int _v, int _d) : v(_v), d(_d) {}
};
struct Dist { // 距离，优先队列优化
    int v, d;
    Dist(int _v, int _d) : v(_v), d(_d) {}
    friend bool operator < (const Dist& a, const Dist& b) {return a.d > b.d;} // 必须加const修饰
};
vector<GNode> adj[MAXN];
int d[MAXN];
bool vis[MAXN] = {false};
int n, m, root;
void prim(int root) {
    int ans = -1; // 保存最大边
    fill(d, d + MAXN, INF); // 初始化为极大值
    d[root] = 0; // 根距离为0
    priority_queue<Dist> pq; // 优先队列
    pq.push(Dist(root, 0));
    for(int i = 0; i < n; i ++) { // n个点
        int k, MIN = INF;
        while(!pq.empty()) {
            if(!vis[pq.top().v]) { // 必须先判断是否访问
                k = pq.top().v;
                MIN = pq.top().d;
                pq.pop();
                break;
            }
            else pq.pop();
        }
        vis[k] = true; // 访问k
        ans = max(ans, MIN);
        for(auto p : adj[k]) { // 更新相邻点
            if(!vis[p.v] && d[p.v] > p.d) {
                d[p.v] = p.d;
                pq.push(Dist(p.v, p.d)); // 压入优先队列
            }
        }
    }
    printf("%d\n", ans);
}
void createGraph() {
    scanf("%d %d %d", &n, &m, &root);
    int u, v, d;
    while(m --) {
        scanf("%d %d %d", &u, &v, &d);
        adj[u].push_back(GNode(v, d));
        adj[v].push_back(GNode(u, d));
    }
}
int main() {
    createGraph();
    prim(root);
    return 0;
}