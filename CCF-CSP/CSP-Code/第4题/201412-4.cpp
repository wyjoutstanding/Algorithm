/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-21 00:18:28 
 * @Last Modified time: 2019-09-21 00:18:28 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
struct Edge {
    int u, v, d; // 边的起止点，边权
};
vector<Edge> edge;
int n, m;
int father[maxn];
int findFather(int x) { // 并查集递归找根节点&&压缩路径
    return x == father[x] ? x : father[x] = findFather(father[x]);
}
void kruskal() {
    for(int i = 0; i < maxn; i ++) father[i] = i; // 初始化
    sort(edge.begin(), edge.end(), [](Edge& a, Edge& b) {return a.d < b.d;}); // 按边权从小到大排序
    int cnt = 0, ans = 0; // 已选边数，边权之和
    for(auto& p : edge) {// 遍历所有边
        int fu = findFather(p.u);
        int fv = findFather(p.v);
        if(fu != fv) { // 两点不通
            // father[p.u] = p.v; // 合并
            father[fu] = fv; // 父节点合并
            cnt ++;
            ans += p.d;
        }
        if(cnt == n - 1) break; // 找到生成树
    }
    printf("%d\n", ans);
}
int main() {
    scanf("%d %d", &n, &m);
    int u, v, d;
    for(int i = 0; i < m; i ++) {
        scanf("%d %d %d", &u, &v, &d);
        edge.push_back(Edge{u, v, d});
    }
    kruskal();
    return 0;
}