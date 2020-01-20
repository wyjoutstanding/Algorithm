/*
 * @Author: wuyangjun
 * @Date: 2019-08-14 15:59:59
 * @LastEditTime: 2019-08-14 16:29:05
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
vector<int> Adj[maxn], ans; // 邻接表、答案
bool vis[maxn]; // 记录是否被访问
int N, nowDepth = -1, maxDepth = -2; // 顶点个数、当前顶点为根的最大深度，所有顶点作为根的最大深度
void dfs(int v, int depth) {
    vis[v] = true;
    if(nowDepth < depth) { // 记录以v为根的最大深度
        nowDepth = depth;
    }
    for(auto p : Adj[v]) { // 访问所有未被访问的相连点
        if(!vis[p]) dfs(p, depth + 1);
    }
}
void dfsTrave() {
    fill(vis, vis + maxn, false); // 初始化
    int cnt = 0; // 统计连通块个数
    for(int v = 1; v <= N; v ++) {
        if(!vis[v]) {
            cnt ++;
            dfs(v, 0);
        }
    }
    if(cnt != 1) printf("Error: %d components\n", cnt);
    else { // 连通，必为树
        for(int v = 1; v <= N; v ++) { // 遍历每个点，以它们作为根求最大深度
            fill(vis, vis + maxn, false); // 初始化
            nowDepth = -1; // 当前最大深度
            dfs(v, 0);
            if(maxDepth < nowDepth) { // 记录全局最大深度
                maxDepth = nowDepth;
                ans.clear();
                ans.push_back(v);
            }
            else if(maxDepth == nowDepth) ans.push_back(v); // 多解
        }
        sort(ans.begin(), ans.end()); // 升序排列
        for(auto p : ans) printf("%d\n", p); 
    }
}
void readData() {
    scanf("%d", &N);
    int a, b;
    for(int i = 0; i < N - 1; i ++) {
        scanf("%d %d", &a, &b);
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }
}
int main() {
    readData();
    dfsTrave();
    return 0;
}