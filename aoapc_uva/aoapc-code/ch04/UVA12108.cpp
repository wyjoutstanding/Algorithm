#include<bits/stdc++.h>
using namespace std;
int n, a, b, c, num=0;
int main() {
    while (cin >>n && n != 0) {
        set<vector<int> > _set; // 死循环判重
        vector<int> stat, tmp, as, bs; // 当前状态，中间变量，清醒持续时间，睡眠持续时间
        for (int i = 0; i < n; i ++) {
            cin >>a >>b >>c;
            as.push_back(a); bs.push_back(b); // 存储左右区间
            stat.push_back(c); // 第一轮状态
            _set.insert(stat); // 保存状态序列
        }
        int cnt = 1, ans = -1;
        while (true) {
            int wknum = 0; // 清醒人数
            for (int i = 0; i < n; i ++) { // 计算清醒人数
                if (1 <= stat[i] && stat[i] <= as[i]) wknum ++;
            }
            if (wknum == n) { // 全部清醒
                ans = cnt;
                break; // 直接结束
            }
            cnt ++;
            tmp = stat; // 开始模拟
            for (int i = 0; i < n; i ++) { // n个人
                if (tmp[i] == as[i]) { // 准备睡觉
                    if (wknum * 2 < n) stat[i] = as[i]+1; // 睡觉人数大于清醒
                    else stat[i] = 1; // 继续清醒
                }
                else stat[i] = (stat[i] == as[i]+bs[i]) ? 1 : stat[i]+1; // 下一个状态 
            }
            if (_set.find(stat) == _set.end()) _set.insert(stat); 
            else break; // 出现重复，死循环
        }
        printf("Case %d: %d\n", ++num, ans);
    }
    return 0;
}