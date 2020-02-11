#include<bits/stdc++.h>
using namespace std;
map<map<char,int>, int>dict; // 每个单词的字母出现次数->出现次数
map<map<char,int>, string> trans; // 单词字母出现次数->原单词
set<string> ans; // 存储输出结果，按字典序排列
string s, st;
int main() {
    while (cin >>s && s!= "#") {
        st = s;
        map<char, int> mp;
        for (auto& ch : st) {
            if (ch >= 'A' && ch <= 'Z') ch = tolower(ch); // 转为小写
            mp[ch] ++; // 统计每个字符出现次数
        }
        dict[mp]++; // 统计次数
        trans[mp] = s; // 记录原单词
    }
    for (auto p : dict) if (p.second == 1) ans.insert(trans[p.first]); // 出现次数1表示非重排单词
    for (auto& p : ans) cout <<p <<endl; // 直接输出剩下的单词
    return 0;
}