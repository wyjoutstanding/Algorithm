/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 13:15:53
 * @LastEditTime: 2019-09-13 13:18:56
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[10010], ans = 0x3fffffff;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a + n); // 升序排列
    for(int i = 0; i < n - 1; i ++) ans = min(ans, a[i+1] - a[i]); // 相邻两点最小差值
    printf("%d\n", ans);
    return 0;
}