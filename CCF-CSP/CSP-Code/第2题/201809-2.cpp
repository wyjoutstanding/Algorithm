/*
 * @Author: wuyangjun
 * @Date: 2019-09-14 15:04:22
 * @LastEditTime: 2019-09-14 15:31:43
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000010;
struct Pos {
    int l, r; // 左右区间
}H[maxn], W[maxn];
int n, l, r, ans = 0;
void solve() {
    int i = 0, j = 0;
    while(i < n && j < n) {
        if(H[i].l <= W[j].r && H[i].r >= W[j].l) { // 存在交集
            ans += min(H[i].r, W[j].r) - max(H[i].l, W[j].l); // 区间
        }
        if(H[i].r == W[j].r) { // 相等，两个同时后移
            i ++;
            j ++;
        }
        else if(H[i].r < W[j].r) i ++; // 右侧小者后移
        else j ++;
    }
    printf("%d\n", ans);
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d %d", &H[i].l, &H[i].r);
    for(int i = 0; i < n; i ++) scanf("%d %d", &W[i].l, &W[i].r);
    solve();
    return 0;
}