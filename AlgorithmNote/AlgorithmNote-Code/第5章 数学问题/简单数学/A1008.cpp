/*
 * @Author: wuyangjun
 * @Date: 2019-08-04 20:18:17
 * @LastEditTime: 2019-08-04 20:27:38
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    LL n;
    scanf("%lld", &n);
    // 分别计算出上楼，下楼，停留的总次数
    LL now = 0, pos = 0, neg = 0, t;
    for(LL i = 0; i < n; i++) {
        scanf("%lld", &t);
        LL tmp = t - now;
        if(tmp > 0) pos += tmp;
        else neg += tmp;
        now = t; 
    }
    printf("%lld\n", pos * 6 + (-neg) * 4 + n * 5);
    return 0;
}