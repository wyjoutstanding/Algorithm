/*
 * @Author: wuyangjun
 * @Date: 2019-09-11 19:43:13
 * @LastEditTime: 2019-09-11 20:14:38
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
struct GNode {
    int v, d;
    GNode(int _v, int _d) : v(_v), d(_d) {}
};
vector<GNode> adj[maxn];
bool vis[maxn] = {false};
int n, m, MAX = -1, ans = 0x3fffffff;
void dfs(int pre, int cur, int c, int MAX) { // 路径的前一个点，当前点，二者距离（时间），当前路径的最大边
    if(c > ans) return; // 剪枝
    vis[cur] = true;
    MAX = max(MAX, c); // 路径中的最大值
    if(cur == n) { // 找到一条合适路径
        ans = min(ans, MAX); // 找最小值
        return;
    }
    for(auto p : adj[cur]) { // 访问邻边
        if(!vis[p.v]) {
            dfs(cur, p.v, p.d, MAX);
            vis[p.v] = false; // 回溯
        }
    }
}
int main() {
    scanf("%d %d", &n, &m);
    int a, b, c;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back(GNode(b, c)); // 无向图
        adj[b].push_back(GNode(a, c));
    }
    dfs(1, 1, 0, -1);
    printf("%d\n", ans);
    return 0;
}