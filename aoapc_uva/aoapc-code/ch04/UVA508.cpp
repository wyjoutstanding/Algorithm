#include<bits/stdc++.h>
using namespace std;
string codetbl[200], code, s;
char ch;
// map<string, set<string> > ctxt; // 上下文，字典序排列
map<string, vector<string> > ctxt; // 上下文，输入顺序排列
int main() {
    while (cin >>ch && ch != '*') {
        cin >>code; codetbl[ch] = code;
    }
    while (cin >>s && s != "*") {
        string st;
        for (auto c : s) st += codetbl[c];
        // ctxt[st].insert(s); // 字典序排列
        ctxt[st].push_back(s);
    }
    while (cin >>s && s != "*") {
        if (ctxt.find(s) != ctxt.end()) { // 存在
            cout <<*ctxt[s].begin();
            if (ctxt[s].size() > 1) cout <<"!";
        }
        else { // 不存在
            int minlen = 0x3ffff; string ans;
            for (auto p : ctxt) {
                if (s == p.first.substr(0,s.size()) || p.first == s.substr(0,p.first.size())) { // 前缀
                    int i = abs((long)p.first.size()-(long)s.size()); 
                    if (minlen >= i) {
                        minlen = i;
                        ans = *p.second.begin();
                    }
                }
            }
            cout <<ans<<"?";
        }
        puts("");
    }
    return 0;
}