/*
 * @Author: wuyangjun
 * @Date: 2019-09-14 09:59:37
 * @LastEditTime: 2019-09-14 10:29:57
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, r, y, g, t[4] = {0}, ans = 0; // int存储4个测试点会溢出
void init() { // 构造循环时钟0~t1~t3~t2分别对应红->绿->黄
    t[1] = r;
    t[3] = r + g;
    t[2] = r + g + y;
}
LL getWaitTime(LL type, LL leftTime) { // 根据出发时灯类型和剩余时间返回当前需等待时间
    LL cur = (t[type] - leftTime + ans) % (r + g + y); // 计算当前状态
    if(cur >=0 && cur < t[1]) return t[1] - cur; // 红灯
    if(cur >= t[1] && cur < t[3]) return 0; // 绿灯
    if(cur >= t[3] && cur < t[2]) return t[2] - cur + r; // 黄灯 
}
void solve() {
    scanf("%lld %lld %lld %lld", &r, &y, &g, &n);
    init();
    LL type, lt;
    while(n --) {
        scanf("%lld %lld", &type, &lt);
        if(type == 0) ans += lt; // 路
        else ans += getWaitTime(type, lt); // 灯
    }
    printf("%lld\n", ans);
}
int main() {
    solve();
    return 0;
}