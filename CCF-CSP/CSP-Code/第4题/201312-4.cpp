/*
 * @Author: wuyangjun 
 * @Create time: 2019-09-26 17:15:43 
 * @Last Modified time: 2019-09-26 17:15:43 
 * @Gitub: https://github.com/wyjoutstanding 
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL mod = 1000000007, n, dp[1002][6] = {0}; // 6个状态:{2},{02},{23},{012},{023},{0123}
int main() {
    scanf("%lld", &n);
    for(int i = 1; i <= n; i ++) { // n次迭代，填表
        dp[i][0] = 1; // 2
        dp[i][1] = (dp[i-1][0] + dp[i-1][1] * 2) % mod; // 02
        dp[i][2] = (dp[i-1][0] + dp[i-1][2]) % mod; // 23
        dp[i][3] = (dp[i-1][1] + dp[i-1][3] * 2) % mod; // 012
        dp[i][4] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][4] * 2) % mod; // 023
        dp[i][5] = (dp[i-1][3] + dp[i-1][4] + dp[i-1][5] * 2) % mod; // 0123
    }
    printf("%lld\n", dp[n][5]);
    return 0;
}