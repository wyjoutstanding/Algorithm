/*
 * @Author: wuyangjun
 * @Date: 2019-08-04 18:40:07
 * @LastEditTime: 2019-08-04 19:58:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
double a[maxn]; //单精度会报错
long long cnt[maxn] = {0};
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lf", &a[i]);
    // 利用上下、左右的对称性，计算左边一半的列和
    for(long long i = 1; i <= n / 2; i++) {
        cnt[i] = (i * (i + 1) / 2 + (n / 2 - i) * i) * 2; //这里使用int会溢出
        if(n % 2 != 0) cnt[i] += i; //奇数，中间一行
        cnt[n - i + 1] = cnt[i]; //左右对称
    }
    if(n % 2 != 0) cnt[n / 2 + 1] = cnt[n / 2] + 1; //奇数，中间一列
    // 计算总和
    double sum = 0.0;
    for(int i = 1; i <= n; i++) {
        sum += a[i] * cnt[i];
    }
    printf("%.2lf\n", sum);
    return 0;
}