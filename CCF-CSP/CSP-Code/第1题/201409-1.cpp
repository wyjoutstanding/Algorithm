/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 15:55:39
 * @LastEditTime: 2019-09-13 15:57:43
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1010], ans = 0;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a + n);
    for(int i = 1; i < n; i ++) {
        if(a[i] - a[i-1] == 1) ans ++;
    }
    printf("%d\n", ans);
    return 0;
}