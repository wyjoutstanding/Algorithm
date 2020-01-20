/*
 * @Author: wuyangjun
 * @Date: 2019-09-05 09:26:11
 * @LastEditTime: 2019-09-05 20:45:43
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
string now, pre, s;
char str[1010];
int main() {
    int n;
    cin >>n >>now;
    getchar();
    while(n --) {
        fgets(str, 1010, stdin);
        s = str;
        s.erase(s.end() - 1);
        if(s.empty()) cout <<now <<endl;
        else {
            if(s[0] != '/') s = now + "/" + s; // 非绝对路径
            s = regex_replace(s, regex("(//+)"), "/");
            while(true) { // /../ -> /**/，与文件中的.区别
                string tmp = s;
                s = regex_replace(s, regex("(/\\.\\./)"), "/**/");
                if(s == tmp) break;
            }
            while(true) { // /./ -> /
                string tmp = s;
                s = regex_replace(s, regex("(/\\./)"), "/");
                if(s == tmp) break;
            }
            while(true) {
                string tmp = s;
                s = regex_replace(s, regex("((^/\\*\\*)|(/[^/]+/\\*\\*))"), "");
                if(tmp == s) break;
            }
            if(s == "/") printf("/\n");
            else {
                if(s.back() == '/') printf("%s\n", s.substr(0, s.size() - 1).c_str());
                else printf("%s\n", s.c_str());
            }
        }
    }
    return 0;
}
// /d2/d3/../d1/../../d2 
// ../1/..d.2./././.././