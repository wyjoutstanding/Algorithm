/*
 * @Author: wuyangjun
 * @Date: 2019-08-14 21:03:52
 * @LastEditTime: 2019-08-14 22:19:40
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005; // 1000条记录，至多2000人！！！
struct GNode {
    int v; // 点
    int w; // 边权
    GNode(int _v, int _w) : v(_v), w(_w) {} // 带参构造
    GNode() {w = 0;} // 默认构造
};
vector<GNode> Adj[maxn]; // 邻接表
bool vis[maxn]; // 访问标记
int weight[maxn] = {0}; // 每个点的总边权
int N = 0, K; // 总结点个数, 阀值
string names[maxn]; // 序号 -> 姓名
map<string, int> ans, nti; // 头目姓名 -> 人数、 姓名 -> 编号
vector<int> tmp; // 临时连通分支
void dfs(int v) {
    vis[v] = true;
    tmp.push_back(v); // 保存路径，即连通分支
    for(auto p : Adj[v]) {
        if(!vis[p.v]) dfs(p.v);
    }
}
void dfsTrave() {
    fill(vis, vis + maxn, false);
    for(int v = 1; v <= N; v ++) {
        if(!vis[v]) { // 每一个连通分支
            dfs(v);
            int maxW = -1, maxV = -1, tot = 0; // 最大值，最大值下标，总边权
            if(tmp.size() >= 3) { // 至少3个人
                for(auto p : tmp) {
                    tot += weight[p];
                    if(maxW < weight[p]) {
                        maxW = weight[p];
                        maxV = p;
                    }
                }
                if(tot / 2 > K) ans[names[maxV]] = tmp.size(); // 记录答案，无向图每条边被计算两次，需除以2
            }
            tmp.clear();
        }
    }
    // 输出
    printf("%d\n", ans.size());
    for(auto p : ans) {
        printf("%s %d\n", p.first.c_str(), p.second);
    }
}
void createGraph() {
    int n;
    scanf("%d %d", &n, &K);
    string a, b;
    int t;
    for(int i = 0; i < n; i ++) {
        cin >>a >>b >>t;
        // 第一次出现的名字进行编码，从1开始
        if(nti.count(a) == 0) {
            nti[a] = (++N); // name -> id
            names[N] = a; // id -> name
        }
        if(nti.count(b) == 0) {
            nti[b] = (++N);
            names[N] = b;
        }
        // 判断边是否第一次出现
        bool isExist = false;
        for(auto& p : Adj[nti[a]]) {
            if(p.v == nti[b]) { // 非第一次
                p.w += t; // 累加边权
                isExist = true;
                // 无向图，另一个点相同处理
                for(auto& q : Adj[nti[b]]) {
                    if(q.v == nti[a]) {
                        q.w += t;
                        break;
                    }
                }
                break;
            }
        }
        if(!isExist) { // 第一次出现的边
            Adj[nti[a]].push_back(GNode(nti[b], t));
            Adj[nti[b]].push_back(GNode(nti[a], t));
        }
    }
    // 计算每个点的总边权
    for(int i = 1; i <= N; i ++) {
        int tot = 0;
        for(auto p : Adj[i]) {
            tot += p.w;
        }
        weight[i] = tot;
    }
}
int main() {
    createGraph();
    dfsTrave();
    return 0;
}