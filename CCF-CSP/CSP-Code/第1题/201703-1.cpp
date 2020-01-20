/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 13:42:28
 * @LastEditTime: 2019-09-13 13:49:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k, ans = 0, sum = 0, t;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        sum += t;
        if(sum >= k) { // 下一个人
            ans ++;
            sum = 0;
        }
    }
    printf("%d\n", ans += (sum == 0) ? 0 : 1); // 最后未分满K的需处理
    return 0;
}