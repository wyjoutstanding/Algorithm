#include <bits/stdc++.h>
using namespace std;
struct money {
     long long g, s, k; //int会溢出
}a, b, res;
int main() {
    scanf("%lld.%lld.%lld", &a.g, &a.s, &a.k);
    scanf("%lld.%lld.%lld", &b.g, &b.s, &b.k);
    // 换算为最小单位
    long long sum;  //数据范围
    sum = a.g * 17 * 29 + a.s * 29 + a.k;
    sum += b.g * 17 * 29 + b.s * 29 + b.k;
    // 转换为要求格式
    res.k = sum % 29;
    sum /= 29;
    res.s = sum % 17;
    sum /= 17;
    res.g = sum;
    printf("%lld.%lld.%lld", res.g, res.s, res.k);
    return 0;
}