/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 11:55:39
 * @LastEditTime: 2019-08-08 11:59:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int ans = -1, cnt = 1, t;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            scanf("%d", &t);
            // 不等，需抵消
            if(ans != t) {
                if(cnt == 1) ans = t; //直接更新ans
                else cnt --;
            }
            else cnt ++; //相等
        }
    }
    printf("%d\n", ans);
    return 0;
}