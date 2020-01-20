/*
 * @Author: wuyangjun
 * @Date: 2019-09-14 18:56:32
 * @LastEditTime: 2019-09-14 19:26:48
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
struct Pos {
    int id, x, dist; // 输入顺序， 位置， 方向：-1左，1右
}a[maxn];
int N, L, T, order[maxn];
int main() {
    scanf("%d %d %d", &N, &L, &T);
    for(int i = 0; i < N; i ++) {
        scanf("%d", &a[i].x);
        a[i].id = i; // 输入顺序
        a[i].dist = 1; // 方向向右
    }
    sort(a, a + N, [](Pos& a, Pos& b) {return a.x < b.x;}); // 按距离从小到达排序
    for(int i = 0; i < N; i ++) order[a[i].id] = i; // 记录每个输入位置对应的实际位置
    for(int i = 0; i < T; i ++) { // T次更新
        int j = 0;
        while(j < N) {
            a[j].x += a[j].dist;
            if(a[j].x == 0 || a[j].x == L) a[j].dist = -a[j].dist; // 边界反转
            else if(j < N - 1 && a[j].x == (a[j+1].x + a[j+1].dist)) { // 两球碰撞
                a[j].dist = -a[j].dist; // 更新方向
                a[j+1].x += a[j+1].dist; // 先更新位置
                a[j+1].dist = -a[j+1].dist;
                j ++; // 后移一位
            }
            j ++;
        }
    }
    for(int i = 0; i < N; i ++) printf("%d ", a[order[i]].x); // 输出
    return 0;
}