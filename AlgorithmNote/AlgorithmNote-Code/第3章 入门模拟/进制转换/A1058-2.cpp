#include <bits/stdc++.h>
using namespace std;
struct money {
     int g, s, k; //无需考虑溢出
}a, b, res;
int main() {
    scanf("%d.%d.%d", &a.g, &a.s, &a.k);
    scanf("%d.%d.%d", &b.g, &b.s, &b.k);
    int carry;  //进位
    res.k = (a.k + b.k) % 29;
    carry = (a.k + b.k) / 29;
    res.s = (a.s + b.s + carry) % 17;
    carry = (a.s + b.s + carry) / 17;
    res.g = (a.g + b.g + carry);
    printf("%d.%d.%d", res.g, res.s, res.k);
    return 0;
}