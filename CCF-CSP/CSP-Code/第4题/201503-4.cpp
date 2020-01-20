/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-19 20:52:15 
 * @Last Modified time: 2019-09-19 20:52:15 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 20010; // n+m
vector<int> adj[maxn]; // 邻接矩阵
int MAX = 0, firstV = 1, vis[maxn] = {0}; // 最大步数，第一个最远点，访问数组
void dfs(int u, int cnt) { // u:当前点；cnt：经过的边数
    vis[u] = true;
    for(auto& v : adj[u]) { // 遍历所有相邻边
        if(!vis[v]) dfs(v, cnt + 1);
    }
    if(MAX < cnt) { // 取最长的一条
        MAX = cnt;
        firstV = u;
    }
}
int main() {
    int n, m, t;
    scanf("%d %d", &n, &m);
    for(int i = 2; i <= n + m; i ++) { // 电脑从n个交换机后编号
        scanf("%d", &t);
        adj[t].push_back(i); // 无向图
        adj[i].push_back(t);
    }
    dfs(1, 0); // 第一次dfs得到一个点
    fill(vis, vis + maxn, 0); // 初始化访问数组
    dfs(firstV, 0); // 第二次dfs得到结果MAX
    printf("%d\n", MAX);
    return 0;
}