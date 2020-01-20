/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 13:28:19
 * @LastEditTime: 2019-08-05 13:58:33
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Fraction {
    LL up;
    LL down;
}sum, t;
// 最大公约数
int gcd(LL a, LL b) {
    if(b == 0) return a;
    else return gcd(b, a % b);
}
// 化简
Fraction reduction(Fraction res) {
    // 保证分母为正
    if(res.down < 0) {
        res.up = -res.up;
        res.down = -res.down;
    }
    // 0：分子为0，分母为1
    if(res.up == 0) res.down = 1;
    else {//化为最简
        int d = gcd(abs(res.up), res.down); //最大公约数,分子必须用绝对值
        res.up /= d;
        res.down /= d;
    }
    return res;
}
// 模拟分数加法
Fraction add(Fraction a, Fraction b) {
    Fraction t;
    t.up = a.up * b.down + b.up * a.down;
    t.down = a.down * b.down;
    return reduction(t); //返回最简结果
}
// 展示结果
void showResult(Fraction res) {
    Fraction r = reduction(res); //化简
    if(r.down == 1) printf("%d\n", r.up); //整数
    else if(abs(r.up) > r.down) printf("%d %d/%d\n", r.up / r.down, abs(r.up) % r.down, r.down); //假分数
    else printf("%d/%d\n", r.up, r.down); //真分数
}
int main() {
    int n;
    scanf("%d", &n);
    sum.up = 0;
    sum.down = 1;
    for(int i = 0; i < n; i++) {
        scanf("%lld/%lld", &t.up, &t.down);
        sum = add(sum, t);
        // printf("%lld/%lld\n", t.up, t.down);
    }
    showResult(sum);
    return 0;
}