/*
 * @Author: wuyangjun
 * @Date: 2019-08-23 14:38:21
 * @LastEditTime: 2019-08-23 15:20:21
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010, INF = 0x7fffffff;
int order[maxn], pos[maxn], a[maxn], dp[maxn]; // 输入期望序列、期望序列对应的下标、输入的颜色序列、以a[i]为结尾的最大序列长度
int main() {
    int N, M, L;
    scanf("%d %d", &N, &M);
    fill(pos, pos + maxn, INF); // 不存在的为无穷大
    int t;
    for(int i = 1; i <= M; i ++) {
        scanf("%d", &order[i]);
        pos[order[i]] = i; // 值- >位置
    }
    scanf("%d", &L);
    for(int i = 1; i <= L; i ++) {
        scanf("%d", &a[i]);
    }
    // 动规
    for(int i = 1; i <= L; i ++) {
        dp[i] = 1; // 初始值
        if(pos[a[i]] == INF) continue; // 不存在就不考虑
        for(int j = 1; j < i; j ++) { // 选最大值
            if(pos[a[j]] <= pos[a[i]] && (dp[i] < dp[j] + 1)) dp[i] = dp[j] + 1;
        }
    }
    // 找最长
    int MAX = -1;
    for(int i = 1; i <= L; i ++) {
        if(dp[i] > MAX) MAX = dp[i];
    }
    printf("%d\n", MAX);
    return 0;
}