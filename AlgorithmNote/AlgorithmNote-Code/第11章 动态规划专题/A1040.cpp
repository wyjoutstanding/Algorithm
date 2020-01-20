/*
 * @Author: wuyangjun
 * @Date: 2019-08-23 19:51:08
 * @LastEditTime: 2019-08-23 20:17:32
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int dp[maxn][maxn] = {0};
int main() {
    string s;
    getline(cin, s);
    // 初始化，长度为1,2的子串
    int ans = 1;
    for(int i = 0; i < s.size(); i ++) {
        dp[i][i] = 1; // 长度为1
        if(i < s.size() - 1 && s[i] == s[i + 1]) {
            dp[i][i + 1] = 2; // 长度为2
            ans = 2; // 选最大值
        }
    }
    // 长度3~N的子串
    for(int i = 3; i <= s.size(); i ++) {
        for(int j = 0; j < s.size() - i + 1; j ++) { // 起点
            int k = j + i - 1; // 终点
            if(s[j] == s[k]) {
                if(dp[j + 1][k - 1] == 0) continue; // 内部子串为非回文，直接跳过
                dp[j][k] = dp[j + 1][k - 1] + 2; // 回文相加，非回文为0
                ans = max(ans, dp[j][k]); // 选最大
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}