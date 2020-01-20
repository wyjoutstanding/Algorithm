/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 10:39:13
 * @LastEditTime: 2019-08-05 11:01:17
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int a[101];
// 打印
void print(int n) {
    for(int i = 0; i < n; i++) {
        if(i == 0) printf("%d", a[i]);
        else printf(" %d", a[i]);
    }
    printf("\n");
}
// 最大公约数
int gcd(int a, int b) {
    if(b == 0) return a;
    else return gcd(b, a % b);
}
// 模拟循环右移
void solve(int n, int m) {
    int d = gcd(n, m);
    // 轮换的组数d
    for(int i = 0; i < d; i++) {
        int j = i;
        // 以a[j]为起点，m为间隔的轮换
        int cur, next = a[j], to;
        do {
            cur = next;
            j = (j + m) % n;
            next = a[j];
            a[j] = cur;
        }while(j != i);
    }
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    m %= n; //m >= n的情况
    // m == 0直接输出即可
    if(m != 0) solve(n, m);
    print(n);
    return 0;
}