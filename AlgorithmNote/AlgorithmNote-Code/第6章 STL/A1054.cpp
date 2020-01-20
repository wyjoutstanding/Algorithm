/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 11:37:28
 * @LastEditTime: 2019-08-08 11:44:50
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    map<int, int> mp;
    int t;
    // 统计每个颜色出现次数
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            scanf("%d", &t);
            if(mp.count(t) == 0) mp[t] = 0; //初始化
            mp[t] ++;
        }
    }
    // 找出最大值
    int ans, maxCnt = 0;
    for(auto p : mp) {
        if(p.second > maxCnt) {
            maxCnt = p.second;
            ans = p.first;
        }
    }
    printf("%d\n", ans);
    return 0;
}