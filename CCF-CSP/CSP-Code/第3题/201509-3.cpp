/*
 * @Author: wuyangjun
 * @Date: 2019-09-06 18:58:19
 * @LastEditTime: 2019-09-06 20:10:55
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
    s = regex_replace(s, regex("(\\{\\{)"), "`{{");
    s = regex_replace(s, regex("(\\}\\})"), "}}`");
    stringstream input(s);
    while(getline(input, tmp, '`')) {
        smatch res;
        if(regex_match(tmp, res, regex("^\\{\\{ ([^ ]+) \\}\\}$"))) {
            if(mp.count(res.str(1)) != 0) {
                ans += mp[res.str(1)];
            }
        }
        else ans += tmp;
    }
    cout <<ans;
    return 0;
}