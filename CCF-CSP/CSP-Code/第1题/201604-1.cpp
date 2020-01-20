/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 15:01:19
 * @LastEditTime: 2019-09-13 15:06:28
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1010], ans = 0;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    for(int i = 1; i < n - 1; i ++) {
        if((a[i] - a[i-1]) * (a[i+1] - a[i]) < 0) ans ++; // 折点：斜率相乘为负
    }
    printf("%d\n", ans);
    return 0;
}