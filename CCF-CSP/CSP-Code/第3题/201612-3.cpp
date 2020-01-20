/*
 * @Author: wuyangjun
 * @Date: 2019-09-03 21:28:54
 * @LastEditTime: 2019-09-03 23:16:10
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
const int MIN = '*'; // 表示不分等级权限
vector<string> auth; // 权限
unordered_map<string, set<string> > role; // 角色名->(权限名，等级)
unordered_map<string, vector<pair<string, char> > > user; // 用户名->(权限名，等级)

void readData() {
    string str;
    int p, r, s, u;
    scanf("%d", &p);
    for(int i = 0; i < p; i ++) { // 权限段
        cin >>str;
        auth.push_back(str);
    }
    scanf("%d", &r);
    for(int i = 0; i < r; i ++) { // 角色段
        string rname; // 角色名
        cin >>rname;
        scanf("%d", &s); // 权限个数
        for(int j = 0; j < s; j ++) {
            cin >>str;
            role[rname].insert(str);
        }
    }
    scanf("%d", &u);
    string uname;
    for(int i = 0; i < u; i ++) { // 用户段
        cin >>uname; // 用户名
        scanf("%d", &s);
        string rname; // 角色名
        set<string> _set; // 去重判断
        for(int j = 0; j < s; j ++) {
            cin >>rname;
            for(auto str : role[rname]) { // 遍历该角色所有权限，重复出现选最大
                string category;
                char level = MIN;
                int pos = str.find(':');
                if(pos != string::npos) { // 分割类别名和权限
                    category = str.substr(0, str.size() - 2);
                    level = str.back();
                }
                else category = str;
                if(_set.count(category) == 0) { // 第一次出现
                    _set.insert(category);
                    user[uname].push_back({category, level});
                }
                else { // 重复出现
                    for(auto &p : user[uname]) {
                        if(p.first == category) { // 取最大
                            p.second = max(p.second, level);
                        }
                    }
                }
            }
        }
    }
}
void query() {
    int q;
    scanf("%d", &q);
    string uname, str;
    for(int i = 0; i < q; i ++) {
        cin >>uname >>str;
        if(user.count(uname) == 0) printf("false\n");
        else {
            string category;
            char level = MIN;
            int pos = str.find(':');
            if(pos != string::npos) { // 分割类别名和权限
                category = str.substr(0, str.size() - 2);
                level = str.back();
            }
            else category = str;
            bool isFind = false;
            for(auto p : user[uname]) {
                if(p.first == category) {
                    if(p.second < level) printf("false\n");
                    else {
                        if(level == MIN && p.second != MIN) printf("%c\n", p.second);
                        else printf("true\n");
                    }
                    isFind = true;
                    break;
                }
            }
            if(!isFind) printf("false\n");
        }
    }
}
int main() {
    readData();
    query();
    return 0;
}