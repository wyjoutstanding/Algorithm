/*
 * @Author: wuyangjun
 * @Date: 2019-09-07 10:31:08
 * @LastEditTime: 2019-09-07 21:01:00
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Record {
    int valid, type; // 是否有效：0无效，1有效；类型，0：buy， 1：sell
    double p; // 价格
    long long s, bNum, sNum, minNum; // 股数，以p为开盘价的购买股数、售卖股数、买卖最小股数
    Record() {valid = 1; bNum = sNum = 0;} // 默认构造初始化
};
vector<Record> a, buy, sell; // 临时存放、有效买、卖记录
int main() {  
    string s, tmp;
    while(getline(cin, s)) { // ctrl+Z暂停
        Record r;
        stringstream input(s);
        input >>tmp;
        if(tmp == "cancel") {
            int idx;
            input >>idx;
            a[idx - 1].valid = 0; // 标记无效
            r.valid = 0; // 自身也无效
        }
        else {
            input >>r.p >>r.s;
            r.valid = 1;
            r.type = (tmp == "buy") ? 0 : 1; // 类型
        }
        a.push_back(r); // 保存
    }
    for(auto& p : a) { // 分离有效买卖记录
        if(p.valid == 1) {
            if(p.type == 0) buy.push_back(p);
            else sell.push_back(p);
        }
    }
    sort(buy.begin(), buy.end(), [](Record& a, Record& b) {return a.p < b.p;}); // 按交易价从小到大排序
    sort(sell.begin(), sell.end(), [](Record& a, Record& b) {return a.p < b.p;});
    double ansP; // 最大交易价格
    long long ans = -1; // 最大成交量
    for(int i = buy.size() - 1; i >= 0; i --) { // 购买股数计算
        buy[i].bNum = (i == buy.size() - 1) ? buy[i].s : buy[i].s + buy[i + 1].bNum;
        for(int j = 0; j < sell.size(); j ++) { // 对当前购买价格p的卖的股数计算
            if(buy[i].p < sell[j].p) break;
            buy[i].sNum += sell[j].s;
        }
        buy[i].minNum = min(buy[i].sNum, buy[i].bNum); // 取小者
        if(buy[i].minNum > ans) { // 更新
            ans = buy[i].minNum;
            ansP = buy[i].p;
        }
    }
    printf("%.2lf %lld\n", ansP, ans);
    return 0;
}