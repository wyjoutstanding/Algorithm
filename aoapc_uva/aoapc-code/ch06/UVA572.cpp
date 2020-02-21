#include<bits/stdc++.h>
using namespace std;
int m, n, dict[8][2]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}}; // 8个方向
char grid[101][101]; // 方格
void dfs(int x, int y) {
    grid[x][y] = '*'; // 标记
    int xx, yy;
    for (int i = 0; i < 8; i ++) { // 8个方向
        xx = x + dict[i][0]; yy = y + dict[i][1];
        if (xx >= 0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] == '@') dfs (xx, yy); // 位置合法&&有油
    }
}
int main() {
    while (scanf("%d %d", &m, &n) == 2 && m != 0) {
        getchar(); // 吸收空行
        for (int i = 0; i < m; i ++) {
            for (int j = 0; j < n; j ++) scanf("%c", &grid[i][j]);
            getchar(); // 吸收空行
        }
        int ans = 0; // 存储结果
        for (int i = 0; i < m; i ++) { // 遍历所有格子
            for (int j = 0; j < n; j ++) {
                if (grid[i][j] == '@') { // 发现油格
                    ans ++; // 数量增加
                    dfs(i, j); // 找连通块
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}