/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 15:39:52
 * @LastEditTime: 2019-09-13 15:41:54
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, m, a[1001][1001];
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) scanf("%d", &a[i][j]);
    }
    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n; j ++) printf("%d ", a[j][m-1-i]);
        printf("\n");
    }
    return 0;
}