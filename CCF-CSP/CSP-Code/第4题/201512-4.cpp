/*
 * @Author: wuyangjun
 * @Date: 2019-09-18 20:29:32
 * @LastEditTime: 2019-09-18 21:16:58
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
bool vis[maxn][maxn] = {false}; // 记录边是否被访问
vector<int> adj[maxn], ansPath; // 邻接表，欧拉路径
int n, m;
void dfs_stack() {
    stack<int> s;
    s.push(1);
    while(!s.empty()) {
        int cur = s.top(), i;
        for(i = 0; i < adj[cur].size(); i ++) {
            int v = adj[cur][i];
            if(!vis[cur][v]) { // 边未访问
                vis[cur][v] = vis[v][cur] = true;
                s.push(v);
                break; // dfs深入跳入下一个点
            }
        }
        if(i == adj[cur].size()) { // 回溯
            ansPath.push_back(cur); // 记录欧拉路径的点
            s.pop(); // 出栈
        }
    }
}
int main() {
    scanf("%d %d", &n, &m);
    int a, b;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); // 无向图
        adj[b].push_back(a);
    }
    for(int i = 1; i <= n; i ++) sort(adj[i].begin(), adj[i].end()); // 排序，使访问结果按字典序排序
    dfs_stack();
    int cnt = count_if(adj + 1, adj + 1 + n, [](vector<int>& a) {return a.size() % 2 == 0;}); // 统计偶度顶点个数
    if(ansPath.size() == m + 1 && (cnt == n || (cnt == n - 2 && adj[1].size() % 2 == 1))) { // 连通图&&（n个偶度顶点||仅2个奇度顶点）
        for(int i = ansPath.size() - 1; i >= 0; i --) printf("%d ", ansPath[i]); // 逆序输出
    }
    else printf("-1\n");
    return 0;
}