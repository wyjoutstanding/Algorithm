/*
 * @Author: wuyangjun
 * @Date: 2019-08-21 23:21:40
 * @LastEditTime: 2019-08-22 09:29:45
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1100, INF = 0x3fffffff;
struct GNode {
    int v, d;
    GNode(int _v, int _d) : v(_v), d(_d) {}
};
vector<GNode> Adj[maxn];
bool vis[maxn];
int d[maxn];
int N, M, K, Ds;
map<string, int> sti; // Gx -> id
map<int, string> its; // id -> Gx
int gNum, ansGas = -1; // 加油站编号：N+1~N+M；目标加油站
double maxDist = -1, avrDist = INF; // 最近房屋、平均距离
void dijkstra(int s) {
    // 初始
    fill(vis, vis + maxn, false);
    fill(d, d + maxn, INF);
    d[s] = 0;
    // N+M轮迭代
    for(int i = 0; i < N + M; i ++) {
        // 最小点
        int MIN = INF, u = -1;
        for(int v = 1; v <= N + M; v ++) {
            if(!vis[v] && d[v] < MIN) {
                MIN = d[v];
                u = v;
            }
        }
        // 访问
        vis[u] = true;
        // 更新
        for(auto p : Adj[u]) {
            if(!vis[p.v] && d[u] + p.d < d[p.v]) {
                d[p.v] = d[u] + p.d;
            }
        }
    }
    // 寻找最近房屋距离的最大值 && 平均距离
    double min = INF, avg = 0; //sum = 0; 
    for(int i = 1; i <= N; i ++) {
        if(d[i] > Ds) return; // 无效
        if(min > d[i]) min = d[i]; //最近房屋
        // sum += (double)d[i];
        avg += (double)d[i] / N;
    }
    // 最近房屋最大值
    if(min > maxDist) {
        ansGas = s;
        maxDist = min;
        // avrDist = sum / N;
        avrDist = avg;
    }
    else if(min == maxDist && avg < avrDist) {
        ansGas = s;
        avrDist = avg;
    }
}
// 将字符串转换为整数
int change(string s) {
    int ret;
    if(s[0] == 'G') { // 汽油站： N+1开始
        s = s.substr(1, s.size());
        stringstream input(s);
        input >>ret;
        ret += N;
    }
    else {
        stringstream input(s);
        input >>ret;
    }
    return ret;
}
void readData() {
    scanf("%d %d %d %d", &N, &M, &K, &Ds);
    gNum = N + 1;
    string a, b;
    int d;
    for(int i = 0; i < K; i ++) {
        cin >>a >>b >>d;
        int u = change(a);
        int v = change(b);
        Adj[u].push_back(GNode(v, d));
        Adj[v].push_back(GNode(u, d));
    }
}
int main() {
    readData();
    // 遍历汽油站
    for(int g = N + 1; g <= N + M; g ++) {
        dijkstra(g);
    }
    if(ansGas == -1) printf("No Solution\n");
    else {
        printf("G%d\n", ansGas - N);
        // maxDist = round(maxDist * 10) / 10 ; // 四舍五入
        // avrDist = round(avrDist * 10) / 10;
        printf("%.1lf %.1lf\n", maxDist, avrDist); 
    }
    return 0;
}