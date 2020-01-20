/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 09:49:10
 * @LastEditTime: 2019-09-13 10:07:39
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int n, a[100010];
vector<pair<int, int> > ans; // 值->类型（0：整数，1：浮点数）
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    ans.push_back({a[1] * 2, 0}); // 两端的最大/最小值
    ans.push_back({a[n] * 2, 0});
    if(n % 2 != 0) ans.push_back({a[(n + 1) / 2] * 2, 0}); // 中位数
    else {
        int tmp = a[n / 2] + a[n / 2 + 1];
        if(tmp % 2 == 0) ans.push_back({tmp, 0});
        else ans.push_back({tmp, 1});
    }
    sort(ans.begin(), ans.end(), [](pair<int, int> a, pair<int, int> b) {return a.first > b.first;}); // 从大到小排序
    for(auto& p : ans) { // 输出
        if(p.second == 0) printf("%d ", p.first / 2);
        else printf("%.1lf ", (double)p.first / 2);
    }
    printf("\n");
    return 0;
}