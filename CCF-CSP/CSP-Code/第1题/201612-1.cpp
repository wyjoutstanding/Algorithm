/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 14:00:54
 * @LastEditTime: 2019-09-13 14:18:14
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1010], small[1010] = {0}, big[1010] = {0}, ans = -1;
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a + n);
    for(int i = 1; i < n; i ++) {
        if(a[i] > a[i - 1]) small[i] = i; // 小于a[i]的个数
        else small[i] = small[i - 1];
        if(a[n - 1 - i] < a[n - i]) big[n - 1 - i] = i; // 大于a[i]的个数
        else big[n - 1- i] = big[n - i];
    }
    for(int i = 0; i < n; i ++) { // 查找中间数
        if(small[i] == big[i]) {
            ans = a[i];
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}