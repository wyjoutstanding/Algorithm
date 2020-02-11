#include<bits/stdc++.h>
using namespace std;
string s;
set<string> _set; // 查询
int main() {
    while (cin >>s) _set.insert(s);
    for (auto p : _set) {
        bool isCpdword = false;
        for (int i = 0; i < p.size()-1 && !isCpdword; i ++) { // 遍历所有左右组合
            if (_set.find(p.substr(0,i+1)) != _set.end() && _set.find(p.substr(i+1)) != _set.end()) // 左右字符串均存在 
                isCpdword = true;
        }
        if(isCpdword) printf("%s\n", p.c_str());
    }
    return 0;
}