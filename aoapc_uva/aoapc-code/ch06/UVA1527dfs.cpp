#include<bits/stdc++.h>
using namespace std;
vector<set<int> > adj; // 邻接表，注意用set存储去重
int vis[52]={0}; // 标记访问数组
int getId(char c1, char c2) { // 获取字符节点的编号
    return (c1 - 'A')*2 + ((c2 == '+') ? 0 : 1); // 注意?:优先级很低，要用括号
}
void connect(char a1, char a2, char b1, char b2) { // 参数分别表示两点的第一二个字符
    if (a1 == '0' || b1 == '0') return; // 任意一点为0均不连接
    adj[getId(a1,a2)^1].insert(getId(b1,b2)); // 有向图构建；异或含义-> (B+)^1=B-
}
bool dfs(int u) { // 判断以顶点u开始是否存在有向图
    vis[u] = -1; // 当前遍历的标记
    for (int v : adj[u]) // 邻边
        if (vis[v] == -1 || (vis[v] == 0 && dfs(v))) return true; // 碰见当前已访问节点，表示存在有向环
    vis[u] = 1; // 回溯时标记为1，表示已访问过，必须在return false之前
    return false; // 到此处表示当前连通块不存在有向环
}
bool find_cycle() { // 检查图是否存在有向环
    memset(vis, 0, sizeof(vis)); // 初始化为0，表示未访问
    for (int i=0; i < 52; i ++) // 遍历所有连通块
        if (vis[i] == 0 && dfs(i)) return true; // 存在一个环
    return false;
}
int main() {
    int n; string s;
    while (cin >>n) {
        adj.clear(); adj.resize(52); // 初始化
        for (int i=0; i < n; i ++) {
            cin >>s;
            for (int i=0; i < 4; i ++) { // 考虑旋转翻转
                for (int j=0; j < 4; j ++)
                    if (i != j) connect(s[i*2],s[i*2+1],s[j*2],s[j*2+1]); // 构建有向图
            }
        }
        printf("%s\n", !find_cycle() ? "bounded" : "unbounded");
    }
    return 0;
}