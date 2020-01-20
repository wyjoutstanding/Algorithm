/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 10:49:17
 * @LastEditTime: 2019-09-13 10:53:16
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int r, y, g, n, sum = 0, type, t;
    scanf("%d %d %d %d", &r, &y, &g, &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d %d", &type, &t);
        if(type == 0 || type == 1) sum += t; // 路段/红灯
        else if(type == 2) sum += (t + r); // 黄灯
    }
    printf("%d\n", sum);
    return 0;
}