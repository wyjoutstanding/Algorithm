#include<bits/stdc++.h>
using namespace std;
string s;
int main() {
    while (cin >>s) {
        list<char> l;
        auto p = l.begin(); // 初始化
        for (auto ch : s) {
            if (ch == '[') p = l.begin(); // 开头
            else if (ch == ']') p = l.end(); // 结尾
            else {
                p = l.insert(p, ch); // 返回插入数据的迭代器
                p ++; // 后移一位
            }
        }
        for (auto ch : l) cout <<ch; // 输出
        puts("");
    }
    return 0;
}