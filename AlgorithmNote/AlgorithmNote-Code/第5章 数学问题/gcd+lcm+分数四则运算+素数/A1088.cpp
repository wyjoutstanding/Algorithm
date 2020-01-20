/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 14:50:33
 * @LastEditTime: 2019-08-05 15:56:54
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// const ll inf = ((1ll) << 62) -2;
struct Fraction {
    ll up, down;
}a, b, res; 
ll gcd(ll a, ll b) {
    return (b == 0) ? a : gcd(b, a % b);
}
Fraction reduction(Fraction res) {
    if(res.down < 0) {
        res.up = -res.up;
        res.down = -res.down;
    }
    if(res.up == 0) res.down = 1;
    else {
        ll d = gcd(abs(res.up), res.down);
        res.up /= d;
        res.down /= d;
    }
    return res;
}
Fraction add(Fraction a, Fraction b) {
    Fraction res;
    res.up = a.up * b.down + b.up * a.down;
    res.down = a.down * b.down;
    return reduction(res);
}
Fraction sub(Fraction a, Fraction b) {
    Fraction res;
    res.up = a.up * b.down - b.up * a.down;
    res.down = a.down * b.down;
    return reduction(res);
}
Fraction mul(Fraction a, Fraction b) {
    Fraction res;
    res.up = a.up * b.up;
    res.down = a.down * b.down;
    return reduction(res);
}
Fraction div(Fraction a, Fraction b) {
    Fraction res;
    if(b.up == 0) { //除数为0，令分母为0，分子为1
        res.down = 0;
        res.up = 1; //仅仅为了分母不被化简为1
        return res;
    }
    else {
        res.up = a.up * b.down;
        res.down = a.down * b.up;
        return reduction(res);
    }
}
void showResult(Fraction res) {
    Fraction r = reduction(res);
    // 除法特例
    if(r.down == 0) printf("Inf"); 
    else {
        // 负数带括号
        if(r.up < 0) printf("(");
        // 整数
        if(r.down == 1) printf("%lld", r.up);
        // 假分数
        else if(abs(r.up) > r.down) printf("%lld %lld/%lld", r.up / r.down, abs(r.up) % r.down, r.down);
        // 真分数
        else printf("%lld/%lld", r.up, r.down);
        if(r.up < 0) printf(")");
    }
}
void print(Fraction a, Fraction b, Fraction res, char op) {
    showResult(a);
    printf(" %c ", op);
    showResult(b);
    printf(" = ");
    showResult(res);
    printf("\n");
} 
int main() {
    scanf("%lld/%lld", &a.up, &a.down);
    scanf("%lld/%lld", &b.up, &b.down);
    char op[4] = {'+', '-', '*', '/'};
    Fraction (*opFunc[4]) (Fraction a, Fraction b) = {add, sub, mul, div};
    for(int i = 0; i < 4; i++) {
        print(a, b, (*opFunc[i]) (a, b), op[i]);
    }
    return 0;
}