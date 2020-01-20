/*
 * @Author: wuyangjun
 * @Date: 2019-09-04 19:29:11
 * @LastEditTime: 2019-09-04 21:39:29
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int> > player[2] = {{{0, 30}}, {{0, 30}}}; // 正反两个玩家攻击和生命
int main() {
    player[0].resize(10); // 初始化
    player[1].resize(10);
    string action;
    int now = 0, n, pos, a, h, d;
    cin >>n;
    while(n --) {
        cin >>action;
        if(action == "summon") {
            cin >>pos >>a >>h; // 位置，攻击力，生命值
            player[now].insert(player[now].begin() + pos, {a, h});
        }
        else if(action == "attack") {
            cin >>a >>d;
            auto& atk = player[now], &dfd = player[(now + 1) % 2]; // 正反方
            atk[a].second -= dfd[d].first; // 必须先攻击完再去删除死亡
            dfd[d].second -= atk[a].first;
            if(atk[a].second <= 0 && a != 0) { // 死亡且不是英雄，删除它
                atk.erase(atk.begin() + a);
            }
            if(dfd[d].second <= 0 && d != 0) {
                dfd.erase(dfd.begin() + d);
            }
        }
        else now = (now + 1) % 2; // 正反方轮换
    }
    if(player[0][0].second > 0 && player[1][0].second > 0) printf("0\n");
    else if(player[0][0].second > 0) printf("1\n");
    else printf("-1\n");
    for(int i = 0; i < 2; i ++) {
        printf("%d\n", player[i][0].second);
        vector<int> ans;
        for(int j = 1; j < 8; j ++) {
            if(player[i][j].second > 0) ans.push_back(player[i][j].second);
        }
        printf("%d", ans.size());
        for(auto p : ans) printf(" %d", p);
        printf("\n");
    }
    return 0;
}