/*
 * @Author: wuyangjun
 * @Date: 2019-09-08 11:01:32
 * @LastEditTime: 2019-09-08 11:25:37
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[1100];
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &a[i]);
    int MAX = *max_element(a, a + n); // 选出最大高度
    int ans = -1; // 保存结果
    for(int h = 1; h <= MAX; h ++) { // 遍历所有高度
        int sum = 0;
        for(int j = 0; j < n; j ++) { // 计算连续的矩形面积
            if(a[j] >= h) sum += h;
            else { // 产生间断的矩形
                ans = max(ans, sum);
                sum = 0;
            }
        }
        ans = max(ans, sum); // 无间断的矩形
    }
    printf("%d\n", ans);
    return 0;
}