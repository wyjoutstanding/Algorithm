/*
 * @Author: wuyangjun
 * @Date: 2019-09-18 18:42:25
 * @LastEditTime: 2019-09-18 19:16:41
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
bool inq[102][102][302] = {false}; // inq[x][y][t]=true表示坐标为（x，y）的点在t时刻无法被访问
struct Pos {
    int x, y, t; // 点坐标及其被访问的时刻
};
int direct[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // 控制方向
int n, m, t;
int bfs() {
    queue<Pos> q;
    q.push(Pos{1, 1, 0}); 
    inq[1][1][0] = true; // 起点(1,1)入队立刻标记为true
    while(!q.empty()) {
        Pos cur = q.front(); q.pop();
        if(cur.x == n && cur.y == m) return cur.t; // 到达终点（n，m）
        for(int i = 0; i < 4; i ++) { // 4个方向
            int x = cur.x + direct[i][0];
            int y = cur.y + direct[i][1];
            if(x >= 1 && x <= n && y >= 1 && y <= m && !inq[x][y][cur.t + 1]) { // x，y合法且(x,y)在t时刻可访问
                q.push(Pos{x, y, cur.t + 1});
                inq[x][y][cur.t + 1] = true;
            }
        }
    }
}
int main() {
    scanf("%d %d %d", &n, &m, &t);
    int r, c, a, b;
    for(int i = 0; i < t; i ++) { 
        scanf("%d %d %d %d", &r, &c, &a, &b);
        for(int j = a; j <= b; j ++) inq[r][c][j] = true; // 时间段赋值
    }
    printf("%d\n", bfs());
    return 0;
}