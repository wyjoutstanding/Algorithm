/*
 * @Author: wuyangjun
 * @Date: 2019-08-23 11:02:37
 * @LastEditTime: 2019-08-23 11:22:54
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010;
int a[maxn], start[maxn], dp[maxn]; // 输入序列、以i为结尾的最大序列和的起点、以i为结尾的最大序列和
int main() {
    int K;
    scanf("%d", &K);
    int negNum = 0; // 负数个数
    for(int i = 0; i < K; i ++) {
        scanf("%d", &a[i]);
        if(a[i] < 0) negNum ++;
    }
    if(negNum == K) {
        printf("%d %d %d\n", 0, a[0], a[K - 1]);
    }
    else {
        // 边界初始化
        dp[0] = a[0];
        start[0] = 0;
        // K-1次迭代
        for(int i = 1; i < K; i ++) {
            if(dp[i-1] + a[i] >= a[i]) { // 包括0
                dp[i] = dp[i-1] + a[i];
                start[i] = start[i-1];
            }
            else {
                dp[i] = a[i];
                start[i] = i;
            }
        }
        // 找出最大值
        int MAX = -0x3fffffff, idx;
        for(int i = 0; i < K; i ++) {
            if(MAX < dp[i]) {
                MAX = dp[i];
                idx = i;
            }
        }
        printf("%d %d %d\n", dp[idx], a[start[idx]], a[idx]);
    }
    return 0;
}