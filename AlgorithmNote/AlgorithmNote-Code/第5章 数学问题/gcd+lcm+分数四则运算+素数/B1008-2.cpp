/*
 * @Author: wuyangjun
 * @Date: 2019-08-05 11:29:29
 * @LastEditTime: 2019-08-05 11:37:08
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
void print(int *a, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d%s", a[i], i + 1 - n ? " " : "\n");
    }
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int a[n];
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    m %= n; // m > n
    // 3次反转
    reverse(a, a + (n - m));
    reverse(a + (n - m), a + n);
    reverse(a, a + n);
    print(a, n);
    return 0;
}