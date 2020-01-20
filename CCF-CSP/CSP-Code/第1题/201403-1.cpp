/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 16:05:06
 * @LastEditTime: 2019-09-13 16:07:01
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, cnt[1010] = {0}, t, ans = 0;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        if(cnt[abs(t)] == 0) cnt[abs(t)] = 1;
        else ans ++;
    }
    printf("%d\n", ans);
    return 0;
}