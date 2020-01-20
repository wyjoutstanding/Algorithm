/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 14:35:26
 * @LastEditTime: 2019-09-13 14:40:12
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1010], ans = -1;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a + n);
    int p1 = lower_bound(a, a + n, a[n / 2]) - a; // 第一个大于等于x的下标
    int p2 = upper_bound(a, a + n, a[n / 2]) - a; // 第一个大于x的下标
    if(p1 == n - p2) ans = a[n / 2];
    printf("%d\n", ans);
    return 0;
}