#include<bits/stdc++.h>
using namespace std;
vector<vector<int> > adj; // 邻接表
int getId(char c1, char c2) { // 获取字符节点的编号
    return (c1 - 'A')*2 + ((c2 == '+') ? 0 : 1); // 注意?:优先级很低，要用括号
}
void connect(char a1, char a2, char b1, char b2) { // 参数分别表示两点的第一二个字符
    if (a1 == '0' || b1 == '0') return; // 任意一点为0均不连接
    adj[getId(a1,a2)^1].push_back(getId(b1,b2)); // 有向图构建；异或含义-> (B+)^1=B-
}
bool bfs() { // 拓扑排序检测是否存在有向环
    int indegree[52]={0}, num=0; // 访问数组, 入度表,入队计算
    for (int i=0; i < 52; i ++) 
        for (auto v : adj[i]) indegree[v] ++; // 入度计算
    queue<int> q;
    for (int i=0; i < 52; i ++) if (indegree[i] == 0) q.push(i); // 队列初始化
    while (!q.empty()) {
        int u=q.front(); q.pop(); num ++; // 统计出队个数
        for (int v : adj[u]) {
            indegree[v] --; // 更新入度表
            if (indegree[v] == 0) q.push(v); // 入度=0则进队
        }
    }
    return num == 52; // 不存在有向环num=52
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
        printf("%s\n", bfs() ? "bounded" : "unbounded");
    }
    return 0;
}