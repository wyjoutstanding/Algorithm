/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-22 23:46:42 
 * @Last Modified time: 2019-09-22 23:46:42 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 202;
typedef long long LL;
struct Node {
    LL x, y, d, addNum, id; // 点坐标、已经过点数、经过可选点个数，顶点编号
    bool isAdd; // 类型，true：可选点；false：一般点
    Node() {d = addNum = isAdd = 0;} // 默认构造初始化
};
vector<Node> graph; // 存储所有点
bool vis[maxn] = {false}; // 标记是否被访问
LL n, m, k, r, ans = 0;
bool isConnection(Node& a, Node& b) { // 判断两点是否相连
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= r * r;
}
void bfs() {
    queue<Node> q;
    q.push(graph[0]); // 初始第一个点入队
    vis[graph[0].id] = true;
    while(!q.empty()) {
        auto p = q.front(); q.pop();
        for(auto next : graph) { // 遍历所有点
            if(!vis[next.id] && isConnection(p, next)) { // 未被访问&&存在边
                if(next.id == 1) { // 到达第二个
                    ans = p.d;
                    printf("%lld\n", ans);
                    return; // 别用break，无法跳出两层循环
                }
                if(next.isAdd && p.addNum + 1 <= k) next.addNum = p.addNum + 1; // 可选点&&可选数目未超k
                next.d = p.d + 1;
                q.push(next);
                vis[next.id] = true;
            }
        }
    }
}
int main() {
    scanf("%lld %lld %lld %lld", &n, &m, &k, &r);
    Node node;
    for(int i = 0; i < n + m; i ++) {
        scanf("%lld %lld", &node.x, &node.y);
        node.id = i; // 编号
        if(i >= n) node.isAdd = true; // 可选点
        graph.push_back(node);
    }
    bfs();
    return 0;
}