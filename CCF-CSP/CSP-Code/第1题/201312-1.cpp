/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 16:13:53
 * @LastEditTime: 2019-09-13 16:19:47
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10100;
int n, a[maxn] = {0}, t, ans = 0, MAX = -1;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) { // 统计每个值出现次数
        scanf("%d", &t);
        a[t] ++;
    }
    for(int i = 0; i < maxn; i ++) { // 找出现次数最多的数，存在多个取最小
        if(MAX < a[i]) {
            MAX = a[i];
            ans = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}