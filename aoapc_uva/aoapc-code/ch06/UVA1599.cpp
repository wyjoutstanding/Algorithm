#include<bits/stdc++.h>
using namespace std;
const int maxn=100001; // 最大顶点数
struct Edge { // 边
    int u, v, c;
    Edge(int _u, int _v, int _c) : u(_u), v(_v), c(_c) {} // 默认构造函数
};
vector<Edge> edge; // 边的缓存，数组下标作为编号
vector<int> G[maxn]; // 邻接表存图，边用编号表示，提高效率；
int n, m, a, b, c;
int d[maxn], vis[maxn]; // d:终点到各个点的距离（层次）；vis：访问数组
void revBfs() { // 从终点开始遍历，计算到每个点的距离
    memset(d, 0, sizeof(d)); memset(vis, 0, sizeof(vis)); // 初始化
    queue<int> q;
    q.push(n-1); vis[n-1] = 1; // 终点入队
    while (!q.empty()) {
        int u = q.front(); q.pop(); // 顶点出队
        for (int e : G[u]) { // 每条邻边
            int v = (u == edge[e].u) ? edge[e].v : edge[e].u;
            if (vis[v] == 0) { // 未访问
                d[v] = d[u] + 1; // 距离/层次更新
                q.push(v);
                vis[v] = 1; // 标记访问
            }
        }
    }
}
void bfs() { // 从起点开始bfs，记录字典序最小的路径
    printf("%d\n", d[0]); // 最短距离
    memset(vis, 0, sizeof(vis)); // 初始化
    vector<int> next{0}, ans;
    for (int i=0; i < d[0]; i ++) { // 分层遍历
        int minColor=0x3fffffff; // 最小颜色值
        for (int u : next) // 该层顶点（找出本层到下一层的最小颜色值）
            for (int e : G[u]) { // 所有边
                int v = (u == edge[e].u) ? edge[e].v : edge[e].u; // 确定下一个顶点
                if (d[u] == d[v]+1 && edge[e].c < minColor) minColor = edge[e].c; // 找出可达终点的最小颜色边  
            }
        ans.push_back(minColor); // 存储最小颜色
        vector<int> tnext; // 临时存储
        for (int u : next) // 将本层到下一层颜色值满足最小的点加入下一轮next
            for (int e : G[u]) {
                int v = (u == edge[e].u) ? edge[e].v : edge[e].u;
                if (d[u] == d[v]+1 && vis[v] == 0 && edge[e].c == minColor) {
                    tnext.push_back(v);
                    vis[v] = 1;
                }
            }
        next = tnext; // 更新next数组
    }
    for (int i=0; i < ans.size(); i ++) printf("%d%s", ans[i], i == ans.size()-1 ? "\n" : " ");
}
int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        edge.clear(); fill(G, G+maxn, vector<int>{}); // 初始化
        while (m --) {
            scanf("%d %d %d", &a, &b, &c);
            if (a == b) continue; // 处理自环
            G[a-1].push_back(edge.size()); // 无向图，从0开始存储
            G[b-1].push_back(edge.size());
            edge.push_back({a-1,b-1,c}); // 边缓存
        }
        revBfs();
        bfs();
    }
    return 0;
}