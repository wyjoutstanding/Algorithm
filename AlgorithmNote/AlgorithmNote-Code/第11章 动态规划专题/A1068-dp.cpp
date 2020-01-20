/*
 * @Author: wuyangjun
 * @Date: 2019-08-24 00:11:31
 * @LastEditTime: 2019-08-24 00:32:50
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 10010, maxv = 110;
int dp[maxn] = {0}, choice[maxn][maxv], flag[maxn] = {false};
int a[maxn] = {0};
int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i ++) scanf("%d", &a[i]);
    sort(a, a + maxn, [](int a, int b){return a > b;}); // 降序，便于选择字典序最小
    for(int i = 0; i < N; i ++) { // N个物品
        for(int v = M; v >= a[i]; v --) { // 滚动数组优化，逆向枚举
            if(dp[v] <= dp[v - a[i]] + a[i]) { //选，相等也选，字典序小
                dp[v] = dp[v - a[i]] + a[i];
                choice[i][v] = 1; 
            }
            else choice[i][v] = 0;
        }
    }
    if(dp[M] != M) printf("No Solution\n");
    else {
        // 找出路径
        int k = N - 1, num = 0, v = M;
        while(k >= 0) {
            if(choice[k][v] == 1) {
                flag[k] = true;
                num ++;
                v -= a[k];
            }
            k --;
        }
        // 输出
        for(int i = N - 1; i >= 0; i --) {
            if(flag[i]) printf("%d%s", a[i], (--num) == 0 ? "\n" : " ");
        }
    }
    return 0;
}