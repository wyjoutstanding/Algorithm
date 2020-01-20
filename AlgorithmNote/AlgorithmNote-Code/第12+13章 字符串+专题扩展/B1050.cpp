/*
 * @Author: wuyangjun
 * @Date: 2019-08-24 22:03:04
 * @LastEditTime: 2019-08-24 22:49:14
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxm = 10010, maxn = 1010;
int ans[maxm][maxn] = {0};
int N, m, n;
vector<int> a;
// 找到差值最小的m，n且m*n = N
void cal_m_n() {
    int sqrn = (int)sqrt(1.0 * N);
    for(int i = sqrn; i >= 1; i --) {
        if(N % i == 0) {
            m = max(i, N / i);
            n = N / m;
            break;
        }
    }
}
// 移动：x，y表示当前坐标，d表示方向，1,2,3,4,分别表示右，下，左，上；val：即将填入的值
void move(int &x, int &y, int &d, int val) {
    switch(d) {
        case 1:
            if(y + 1 == n || ans[x][y + 1] != 0) { // 需向下转
                x ++;
                d = 2; // 方向向下
            }
            else y ++; // 正常右走
            break;
        case 2:
            if(x + 1 == m || ans[x + 1][y] != 0) { // 左转
                y --;
                d = 3;
            }
            else x ++;
            break;
        case 3:
            if(y == 0 || ans[x][y - 1] != 0) { // 上转
                x --;
                d = 4;
            }
            else y --;
            break;
        case 4:
            if(x == 0 || ans[x - 1][y] != 0) { // 右转
                y ++;
                d = 1;
            }
            else x --;
            break;
    }
    ans[x][y] = val; // 填入值
}
int main() {
    scanf("%d", &N);
    cal_m_n();
    int t;
    for(int i = 0; i < N; i ++) {
        scanf("%d", &t);
        a.push_back(t);
    }
    sort(a.begin(), a.end(), [](int a, int b) {return a > b;}); //降序排列
    // 模拟顺时针填入
    int x = 0, y = 0, d = 1;
    ans[0][0] = a[0]; // 初值
    for(int i = 1; i < N; i ++) move(x, y, d, a[i]);
    // 输出
    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n; j ++) {
            printf("%d%s", ans[i][j], j == n - 1 ? "\n" : " ");
        }
    }
    return 0; 
}