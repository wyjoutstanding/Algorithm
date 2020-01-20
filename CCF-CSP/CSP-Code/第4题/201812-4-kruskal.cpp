/*
 * @Author: wuyangjun
 * @Date: 2019-09-09 08:55:33
 * @LastEditTime: 2019-09-09 09:13:28
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 50010;
struct Edge {
    int u, v, d;
    Edge(int _u, int _v, int _d) : u(_u), v(_v), d(_d) {}
    friend bool operator < (const Edge& a, const Edge& b) {return a.d > b.d;}
};
priority_queue<Edge> edge; // 优先队列边
int n, m, root, father[maxn];
int findFather(int x) { // 递归找到根节点并路径压缩
    if(x == father[x]) return x;
    int tmp = findFather(father[x]);
    father[x] = tmp; // 路径压缩
    return tmp;
}
void kruskal() {
    for(int i = 0; i < maxn; i ++) father[i] = i; // 初始化
    int ans = 0, cnt = 0; // MST最大边，边数
    while(!edge.empty()) { // 优先队列非空
        auto e = edge.top();
        edge.pop();
        int fa = findFather(e.u), fb = findFather(e.v);
        if(fa != fb) { // 不在同一集合
            father[fa] = fb; // 合并
            cnt ++;
            ans = e.d; // 更新最大边
            if(cnt == n - 1) break; // n-1条边结束
        }
    }
    printf("%d\n", ans);
}
int main() {
    scanf("%d %d %d", &n, &m, &root);
    int u, v, d;
    while(m --) {
        scanf("%d %d %d", &u, &v, &d);
        edge.push(Edge(u, v, d));
    }
    kruskal();
    return 0;
}