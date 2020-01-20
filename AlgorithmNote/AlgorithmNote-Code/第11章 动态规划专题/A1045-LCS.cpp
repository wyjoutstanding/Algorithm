/*
 * @Author: wuyangjun
 * @Date: 2019-08-23 15:46:51
 * @LastEditTime: 2019-08-23 16:02:08
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxc = 210, maxn = 10010;
int a[maxc], b[maxn], dp[maxc][maxn];
int main() {
    int N, M, L;
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= M; i ++) scanf("%d", &a[i]);
    scanf("%d", &L);
    for(int i = 1; i <= L; i ++) scanf("%d", &b[i]);
    // 初始化
    for(int i = 1; i <= M; i ++) dp[i][0] = 0;    
    for(int j = 1; j <= L; j ++) dp[0][j] = 0;    
    for(int i = 1; i <= M; i ++) {
        for(int j = 1; j <= L; j ++) {
            int MAX = max(dp[i-1][j], dp[i][j-1]);
            if(a[i] == b[j]) dp[i][j] = MAX + 1;
            else dp[i][j] = MAX;
        }
    }
    printf("%d\n", dp[M][L]);
    return 0;
}