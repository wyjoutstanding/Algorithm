#include<bits/stdc++.h>
using namespace std;
map<string, int> dict; // 标准化单词->出现次数
map<string, string> trans; // 单词字母出现次数->原单词
set<string> ans; // 存储输出结果，按字典序排列
string s, st;
int main() {
    while (cin >>s && s!= "#") {
        st = s;
        for (auto& ch : st) // 转为小写
            if (ch >= 'A' && ch <= 'Z') ch = tolower(ch); // 转为小写
        sort(st.begin(), st.end()); // 升序排列，顺序无关
        dict[st]++; // 统计次数
        trans[st] = s; // 记录原单词
    }
    for (auto p : dict) if (p.second == 1) ans.insert(trans[p.first]); // 出现次数1表示非重排单词
    for (auto& p : ans) cout <<p <<endl; // 直接输出剩下的单词
    return 0;
}