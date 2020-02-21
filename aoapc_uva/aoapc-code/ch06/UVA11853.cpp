#include<bits/stdc++.h>
using namespace std;
#define SQU(x) ((x)*(x)) // 平方宏，注意都要加括号
const int maxn=1010; // 最大圆数量
int n, vis[maxn]={0}; // 访问数组
double x[maxn], y[maxn], r[maxn], ansl, ansr; // 坐标(x,y);r为半径;左边界最小点，右边界最小点
bool isIntersect(int c1, int c2) { // 判断两个圆是否相交：圆心距 < (r1+r2)  
    return SQU(x[c1]-x[c2]) + SQU(y[c1]-y[c2]) < SQU(r[c1]+r[c2]);
}
void calLR (int c) { // 计算每个连通块与左右边界最南处交点
    if (x[c] < r[c]) { // 与左边界相交
        double t = y[c] - sqrt(SQU(r[c]) - SQU(x[c]));
        if (t < ansl) ansl = t;  
    }
    if (x[c] + r[c] > 1000) { // 与右边界相交
        double t = y[c] - sqrt(SQU(r[c]) - SQU(1000-x[c]));
        if (t < ansr) ansr = t;
    }
}
bool dfs(int c) { // 判断能否从北边界走到南边界
    vis[c] = 1; // 标记为已访问
    if (y[c] < r[c]) return true; // 不取等，碰到南边界，即直线y=0
    for (int i=0; i < n; i ++) if (vis[i]==0 && isIntersect(c,i) && dfs(i)) return true; // 遍历连通块
    calLR(c); // 计算左右边界
    return false; // 到这里说明
}
int main() {
    while (scanf("%d", &n) == 1) {
        for (int i=0; i < n; i ++) scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
        memset(vis, 0, sizeof(vis)); ansl = ansr = 1000.0; // 初始化
        bool isWin=true;
        for (int i=0; i < n; i ++) // 遍历n个圆
            if (y[i]+r[i] > 1000 && dfs(i)) { // 与上边界相交且能走到下边界
                isWin = false;
                break;
            }
        if (isWin) printf("0.00 %.2lf 1000.00 %.2lf\n", ansl, ansr);
        else puts("IMPOSSIBLE");
    }
    return 0;
}