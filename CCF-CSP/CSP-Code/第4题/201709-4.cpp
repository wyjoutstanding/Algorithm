/*
 * @Author: wuyangjun
 * @Date: 2019-09-11 09:45:43
 * @LastEditTime: 2019-09-11 15:57:17
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
struct GNode {
    int v;
    GNode(int _v) : v(_v) {}
};
vector<GNode> adj[maxn]; // 邻接表，图
int n, m, now, vis[maxn];
int cnt[maxn][maxn] = {false}; // 记录两个点间是否存在通路，用set会超时
void dfs(int u) {
    vis[u] = true;
    cnt[now][u] = cnt[u][now] = true;
    for(auto p : adj[u]) {
        if(!vis[p.v]) {
            dfs(p.v);
        }
    }
}
int main() {
    scanf("%d %d", &n, &m);
    int u, v, ans = 0;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &u, &v);
        adj[u].push_back(GNode(v)); // 有向边
    }
    for(int u = 1; u <= n; u ++) {
        fill(vis, vis + maxn, false);
        now = u;
        dfs(u);
    }
    for(int i = 1; i <= n; i ++) {
        if(count(cnt[i] + 1, cnt[i] + n + 1, true) == n) ans ++;
    }
    printf("%d\n", ans);
    return 0;
}