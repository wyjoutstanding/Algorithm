/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 08:34:10
 * @LastEditTime: 2019-08-05 08:41:50
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
    LL n;
    scanf("%lld", &n);
    LL a = 1, left, right, now, sum = 0;
    while(n / a != 0) {
        right = n % a;
        now = (n / a) % 10;
        left = n / a / 10;
        if(now == 0) sum += left * a;
        else if(now == 1) sum += left * a + right + 1;
        else sum += (left + 1) * a;
        a *= 10;
    }
    printf("%lld\n", sum);
    return 0;
}