/*
 * @Author: wuyangjun
 * @Date: 2019-09-06 08:31:20
 * @LastEditTime: 2019-09-06 14:46:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int m, n, q;
char a[101][101];
int X[4] = {0, 0, -1, 1}; // X,Y配合作为向量，即上下左右四个方向
int Y[4] = {1, -1, 0, 0};
void print(int n, int m) { // 打印图像
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            printf("%c", a[i][j]); // 别习惯加空格
        }
        printf("\n");
    }
}
void bfs(int x, int y, char ch) { // bfs填充，队列模拟
    queue<pair<int, int> > q;
    a[x][y] = ch; // 入队前标记
    q.push({x, y});
    pair<int, int> p;
    while(!q.empty()) {
        p = q.front();
        q.pop();
        for(int i = 0; i < 4; i ++) { // 4个方向
            int curX = p.first + X[i], curY = p.second + Y[i];
            if(curX >= 0 && curX < n && curY >= 0 && curY < m) { // 界内
                char tmp = a[curX][curY];
                if(tmp != '-' && tmp != '|' && tmp != '+' && tmp != ch) { // 非线段且未填充
                    a[curX][curY] = ch;
                    q.push({curX, curY});
                }
            }
        }
    }
}
void horizon(int y, int x1, int x2) { // 水平线
    int left = min(x1, x2), right = max(x1, x2);
    for(int x = left; x <= right; x ++) {
        if(a[y][x] == '|') a[y][x] = '+';
        else if(a[y][x] != '+') a[y][x] = '-';
    }
}
void vertical(int x, int y1, int y2) { // 垂直线
    int down = min(y1, y2), up = max(y1, y2);
    for(int y = down; y <= up; y ++) {
        if(a[y][x] == '-') a[y][x] = '+';
        else if(a[y][x] != '+') a[y][x] = '|';
    }
}
int main() {
    fill(a[0], a[0] + 101 * 101, '.'); // 初始化.
    scanf("%d %d %d", &m, &n, &q);
    int t, x1, y1, x2, y2, x, y, c;
    while(q --) {
        scanf("%d", &t);
        if(t == 0) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if(y1 == y2) { // 水平
                horizon(n - 1 - y1, x1, x2); // 笛卡尔坐标->矩阵坐标->数组坐标
            }
            else { // 垂直
                vertical(x1, n - 1 - y1, n - 1 - y2);
            }
        }
        else { // 填充
            scanf("%d %d %c", &x, &y, &c);
            bfs(n - 1 - y, x, c);
        }
    }
    print(n, m);
    return 0;
}