/*
 * @Author: wuyangjun
 * @Date: 2019-09-10 21:45:58
 * @LastEditTime: 2019-09-11 00:49:10
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int a[4][4]; // 模拟棋盘
bool isWin(int k) { // 判断k是否获胜
    for(int i = 1; i <= 3; i ++) { // 行列
        if(a[i][1] == k && a[i][2] == k && a[i][3] == k) return true;
        if(a[1][i] == k && a[2][i] == k && a[3][i] == k) return true;
    }
    if(a[1][1] == k && a[2][2] == k && a[3][3] == k) return true; // 对角线
    if(a[1][3] == k && a[2][2] == k && a[3][1] == k) return true; // 斜对角线
    return false; 
}
int dfs(int k) { // 当前执棋者为k，返回二者均采用最优策略的最终结果
    int space = 0; // 空格个数
    for(int i = 1; i <= 3; i ++) {
        for(int j = 1; j <= 3; j ++) if(a[i][j] == 0) space ++; // 统计空格个数
    }
    if(isWin(1)) return space + 1; // Alice胜
    if(isWin(2)) return -(space + 1); // Bob胜
    if(space == 0) return 0; // 满了，平局
    int MIN = 0x3fffffff, MAX = -0x3fffffff; // 体现博弈，均选择最优策略
    for(int i = 1; i <= 3; i ++) { // 遍历所有空格
        for(int j = 1; j <= 3; j ++) {
            if(a[i][j] == 0) { // 空格
                a[i][j] = k; // 填入
                if(k == 1) MAX = max(MAX, dfs(2)); // 最大得分 -> Alice采用最优策略
                if(k == 2) MIN = min(MIN, dfs(1)); // 最小得分 -> Bob采用最优策略
                a[i][j] = 0; // 回溯，为之后搜索准备
            }
        }
    }
    if(k == 1) return MAX;
    if(k == 2) return MIN;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int t = 0; t < n; t ++) {
        for(int i = 1; i <= 3; i ++) {
            for(int j = 1; j <= 3; j ++) {
                scanf("%d", &a[i][j]);
            }
        }
        printf("%d\n", dfs(1));
    }
    return 0;
}