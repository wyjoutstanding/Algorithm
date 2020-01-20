/*
 * @Author: wuyangjun
 * @Date: 2019-09-05 20:52:26
 * @LastEditTime: 2019-09-05 21:11:12
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
string nowPath;
int main() {
    int n;
    cin >>n >>nowPath;
    getchar();
    string s, tmp;
    while(n --) {
        getline(cin, s);
        if(s.empty()) printf("%s\n", nowPath.c_str()); // 空串输出当前路径
        else {
            vector<string> ans;
            if(s[0] != '/') s = nowPath + "/" + s; // 非绝对路径直接加上当前路径
            s = regex_replace(s, regex("(//+)"), "/"); // 正则将//+替换为/
            stringstream input(s.substr(1));
            while(getline(input, tmp, '/')) { // 分割路径
                if(tmp == ".") continue;
                else if(tmp == "..") {
                    if(!ans.empty()) ans.pop_back();
                }
                else ans.push_back(tmp);
            }
            printf("/");
            for(int i = 0; i < ans.size(); i ++) 
                printf("%s%s", ans[i].c_str(), i == ans.size() - 1 ? "\n" : "/");
            if(ans.size() == 0) printf("\n"); // 根目录特判
        }
    }
    return 0;
}