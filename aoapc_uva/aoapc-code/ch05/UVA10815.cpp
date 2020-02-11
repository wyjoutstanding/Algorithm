#include<bits/stdc++.h>
using namespace std;
string text, s;
set<string> dict; // 词典
int main() {
    while (getline(cin, s)) {
        for (auto& ch : s) {
            if (isalpha(ch)) ch = tolower(ch); // 替换小写
            else ch = ' '; // 替换空格 
        }
        text += " "+s; // 拼接文本，注意空格，避免两行尾首直接相连
    }
    stringstream input(text); // 按空格分割
    while (input >>s) dict.insert(s); // 插入去重
    for (auto p : dict) cout <<p <<endl;
    return 0;
}