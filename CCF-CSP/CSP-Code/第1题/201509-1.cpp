/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 15:21:09
 * @LastEditTime: 2019-09-13 15:22:23
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, t, ans = 0, pre = -1;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        if(pre != t) {
            ans ++;
            pre = t;
        }
    }
    printf("%d\n", ans);
    return 0;
}