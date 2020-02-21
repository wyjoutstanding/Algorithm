#include<bits/stdc++.h>
using namespace std;
int n, m, a, b;
void update(vector<int>& indegree, queue<int>& q) { // 更新队列
    for (int i = 1; i <= n; i ++) {
        if (indegree[i] == 0) { // 入度为0
            q.push(i); // 入队
            indegree[i] = -1; // 标记为已访问
        }
    }
}
int main() {
    while (cin >>n >>m && (n != 0 || m != 0)) { // 仅m=0是合法的，如n=5,m=0
        vector<vector<int> > adj(n+1); // 邻接矩阵
        vector<int> indegree(n+1), ans; // 入度表，从1开始；存储结果
        while (m --) {
            cin >>a >>b;
            adj[a].push_back(b);
            indegree[b] ++; // 入度累加
        }
        queue<int> q; update(indegree, q); // 初始化
        while (!q.empty()) {
            int u = q.front(); q.pop(); ans.push_back(u);
            for (int v : adj[u]) indegree[v] --; // 更新入度表
            update(indegree, q); // 更新队列
        }
        for (int i = 0; i < ans.size(); i ++) printf("%d%s", ans[i], i == ans.size()-1 ? "\n" : " ");
    }
    return 0;
}