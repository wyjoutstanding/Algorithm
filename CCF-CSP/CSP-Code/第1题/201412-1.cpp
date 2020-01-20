/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 15:50:07
 * @LastEditTime: 2019-09-13 15:51:08
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, cnt[1010] = {0}, t;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &t);
        cnt[t] ++;
        printf("%d ", cnt[t]);
    }
    return 0;
}