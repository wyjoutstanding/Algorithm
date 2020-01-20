/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 14:49:18
 * @LastEditTime: 2019-09-13 14:51:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1010], ans = -1;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    for(int i = 1; i < n; i ++) ans = max(ans, abs(a[i] - a[i - 1])); //找相邻差值最大者
    printf("%d\n", ans);
    return 0;
}