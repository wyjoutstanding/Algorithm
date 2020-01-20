/*
 * @Author: wuyangjun
 * @Date: 2019-09-14 19:46:37
 * @LastEditTime: 2019-09-14 19:54:15
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 110;
struct Pos {
    int id, x; // 输入顺序， 位置
}a[maxn];
int N, L, T, order[maxn];
int main() {
    scanf("%d %d %d", &N, &L, &T);
    for(int i = 0; i < N; i ++) {
        scanf("%d", &a[i].x);
        a[i].id = i; // 输入顺序
    }
    sort(a, a + N, [](Pos& a, Pos& b) {return a.x < b.x;}); // 按距离从小到达排序
    for(int i = 0; i < N; i ++) order[a[i].id] = i; // 记录每个输入位置对应的实际位置
    for(int i = 0; i < N; i ++) { // N个点更新位置
        int tmp = (a[i].x + T) % (2*L); // 2L为一周期
        if(tmp > L) a[i].x = L - (tmp % L); // 大于L，等于从最右边往回走
        else a[i].x = tmp;
    }
    sort(a, a + N, [](Pos& a, Pos& b) {return a.x < b.x;}); // 按距离从小到达排序，相对位置一致
    for(int i = 0; i < N; i ++) printf("%d ", a[order[i]].x); // 输出
    return 0;
}