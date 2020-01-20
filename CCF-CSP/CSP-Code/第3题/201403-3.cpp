/*
 * @Author: wuyangjun
 * @Date: 2019-09-08 09:23:46
 * @LastEditTime: 2019-09-08 10:27:46
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
unordered_map<string, int> opt; // 接受选项->带参数与否 ，0：不带，1：带
int main() {
    string s;
    cin >>s;
    int i = 0;
    while(i < s.size()) {
        string tmp = "-";
        tmp.push_back(s[i]);
        if(i < s.size() - 1 && s[i+1] == ':') {
            opt[tmp] = 1;
            i ++;
        }
        else opt[tmp] = 0;
        i ++;
    }
    int n;
    string tmp, arg;
    scanf("%d", &n);
    getchar();
    for(int i = 1; i <= n; i ++) {
        getline(cin, s);
        stringstream input(s);
        getline(input, tmp, ' ');
        map<string, string> ans; // 存放选项和参数结果
        while(getline(input, tmp, ' ')) {
            if(tmp[0] != '-' || opt.count(tmp) == 0) break; // 不是命令选项或没有此命令选项
            if(opt[tmp] == 0) ans[tmp] = ""; // 不带参数
            if(opt[tmp] == 1) { // 带参数
                if(getline(input, arg, ' ')) ans[tmp] = arg; // 更新参数
                else break; // 不存在参数
            }
        }
        printf("Case %d:", i); // 打印
        for(auto& p : ans) {
            printf(" %s", p.first.c_str());
            if(!p.second.empty()) printf(" %s", p.second.c_str());
        }
        printf("\n");
    }
    return 0;
}