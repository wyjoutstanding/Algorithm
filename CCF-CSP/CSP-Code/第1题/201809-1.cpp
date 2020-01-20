/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 11:00:37
 * @LastEditTime: 2019-09-13 11:03:45
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1010];
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    for(int i = 0; i < n; i ++) {
        if(i == 0) printf("%d ", (a[0] + a[1]) / 2);
        else if(i == n - 1) printf("%d ", (a[n - 2] + a[n - 1]) / 2);
        else printf("%d ", (a[i-1] + a[i] + a[i+1]) / 3);
    }
    return 0;
}