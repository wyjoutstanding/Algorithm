/*
 * @Author: wuyangjun
 * @Date: 2019-09-06 20:56:55
 * @LastEditTime: 2019-09-06 21:16:04
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
map<string, string> mp; // 变量 -> 值
string s, var, val, ans, tmp;
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    getchar();
    char str[1000];
    while(m --) {
        fgets(str, 1000, stdin);
        s += (string)str;
    }
    while(n --) {
        scanf("%s ", str);
        var = str;
        getline(cin, val);
        val = val.substr(1, val.size() - 2);
        mp.insert({var, val});
    }
    auto i = 0;
    do {
        auto j = s.find("{{", i), k = s.find("}}", i); // 从i开始找到第一个{{和}}
        if(j != string::npos && k != string::npos) { // 变量存在
            for(; i < j; i ++) printf("%c", s[i]); // 输出从i开始的匹配的变量间字符
            tmp = s.substr(j + 3, k - j - 4); // 变量名
            if(mp.count(tmp) != 0) printf("%s", mp[tmp].c_str()); // 变量名的值存在，直接输出
            i = k + 2; // 更新下标
        }
        else for(; i < s.size(); i ++) printf("%c", s[i]); // 匹配结束，输出剩余字符
    }while(i < s.size());
    return 0;
}