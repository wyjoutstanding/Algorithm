/*
 * @Author: wuyangjun
 * @Date: 2019-09-06 20:29:29
 * @LastEditTime: 2019-09-06 20:56:20
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
    auto i = s.cbegin(); // regex_search需要const_iterator类型变量
    smatch res;
    while(regex_search(i, s.cend(), res, regex("\\{\\{ ([^ ]+) \\}\\}"))) { // 搜索匹配变量
        for(; i != res[0].first; i ++) printf("%c", *i); // 输出匹配前的字符
        if(mp.count(res[1]) != 0) printf("%s", mp[res[1]].c_str()); // 若存在变量，直接输出
        i = res[0].second; // 更换下标，下一次搜索
    }
    for(; i != s.cend(); i ++) printf("%c", *i); // 输出剩余字符
    return 0;
}