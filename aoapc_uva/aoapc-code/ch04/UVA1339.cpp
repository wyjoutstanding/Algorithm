#include<bits/stdc++.h>
using namespace std;
int main() {
    string sa, sb;
    vector<int> cnta(26), cntb(26); // 统计个数
    while(cin >>sa >>sb) {
        fill(cnta.begin(), cnta.end(), 0); // 初始化
        fill(cntb.begin(), cntb.end(), 0);
        for (auto ch : sa) cnta[ch-'A'] ++; // 统计字符出现次数
        for (auto ch : sb) cntb[ch-'A'] ++;
        sort(cnta.begin(), cnta.end()); // 排序
        sort(cntb.begin(), cntb.end());
        printf("%s\n", (cnta == cntb) ? "YES" : "NO");
    }
    return 0;
}