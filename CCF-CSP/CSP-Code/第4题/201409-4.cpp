/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-21 23:27:06 
 * @Last Modified time: 2019-09-21 23:27:06 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1002;
int a[maxn][maxn] = {0}; // 0表示正常点，-1：店家，正数：买家，-3：不通点
int n, m, k, d;
long long ans = 0;
struct Node {
    int x, y, d; // 点坐标、该点到店家的最近距离
};
int dict[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // 控制方向
queue<Node> q;
void bfs() {
    while(!q.empty()) {
        auto p = q.front(); q.pop();
        for(int i = 0; i < 4; i ++) { // 4个方向
            int x = dict[i][0] + p.x;
            int y = dict[i][1] + p.y;
            if(x >= 1 && x <= n && y >= 1 && y <= n && a[x][y] != -3) {
                if(a[x][y] != 0) ans += (p.d + 1) * a[x][y]; // 买家
                q.push(Node{x, y, p.d + 1});
                a[x][y] = -3; // 入队标记
            }
        }        
    }
    printf("%lld\n", ans); // int会溢出
}
int main() {
    scanf("%d %d %d %d", &n, &m, &k, &d);
    int x, y, c;
    while(m --) {
        scanf("%d %d", &x, &y);
        a[x][y] = -1; // 店家
        q.push(Node{x, y, 0}); // 压入队列
        a[x][y] = -3; // 表示入队
    }
    while(k --) {
        scanf("%d %d %d", &x, &y, &c);
        a[x][y] += c; // 一个点可能多个买家
    }
    while(d --) {
        scanf("%d %d", &x, &y);
        a[x][y] = -3; // 不通点
    }
    bfs();
    return 0;
}