/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-19 18:51:45 
 * @Last Modified time: 2019-09-19 18:51:45 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 10010;
vector<int> adj[maxn]; // 邻接表
stack<int> path; //dfs经过的路径
int dfn[maxn], low[maxn], idx = 1, ans = 0; // dfn[i]表示顶点i被访问的顺序，low[i]表示i和以i为根的子树的所有点所能到达的最先被访问的顶点
bool vis[maxn] = {0}, instack[maxn] = {0}; // instack[u]=false表示顶点u不在栈中
void tarjan(int u) {
    dfn[u] = low[u] = idx ++; // 初始化
    vis[u] = true; // 访问
    path.push(u); // 压入路径
    instack[u] = 1; // 标记在路径中
    for(auto& v : adj[u]) { // 访问邻边
        if(!vis[v]) { // 未访问
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(instack[v]) { // 已访问&&在栈中
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) { // 找到一个强连通分支的根
        int sum = 0;
        while(!path.empty()) {
            int cur = path.top(); path.pop();
            instack[cur] = 0; // 表示不在路径中
            sum ++;
            if(cur == u) break;
        }
        ans += (sum - 1) * sum / 2;
    }
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a, b;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); // 单向边
    }
    for(int i = 1; i <= n; i ++) { // 处理连通分支
        if(!vis[i]) tarjan(i);
    }
    printf("%d\n", ans);
    return 0;
}