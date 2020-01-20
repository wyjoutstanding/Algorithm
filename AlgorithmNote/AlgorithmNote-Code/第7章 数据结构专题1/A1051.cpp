/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 19:21:23
 * @LastEditTime: 2019-08-08 19:48:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    int t;
    for(int i = 0; i < k; i ++) {
        stack<int> res;
        int idx = 0; //当前最大值
        for(int j = 0; j < n; j ++) {
            scanf("%d", &t);
            if(t > idx) {
                // 小于等于t的值必须先入栈
                for(int x = idx + 1; x <= t; x ++) {
                    res.push(x);
                }
                idx = t;
            }
            // 不超出栈的范围且与栈顶相同
            if(res.size() <= m && t == res.top()) res.pop();
        }
        if(res.empty()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}