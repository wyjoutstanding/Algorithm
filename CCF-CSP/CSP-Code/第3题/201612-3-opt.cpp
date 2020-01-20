/*
 * @Author: wuyangjun
 * @Date: 2019-09-04 08:28:11
 * @LastEditTime: 2019-09-04 09:26:24
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
unordered_map<string, unordered_map<string, int> > role; // 角色对应的权限名和等级
unordered_map<string, unordered_map<string, int> > user; // 用户对应的权限名和等级
pair<string, int> split(string& s) { // 分割得到权限名和等级
    int pos = s.find(':');
    int level = (pos == string::npos) ? -1 : stoi(s.substr(pos + 1, 1)); // 等级默认-1，表示不分等级
    return make_pair(s.substr(0, pos), level); // 构造序偶对
}
int main() {
    int p, r, s, u, q;
    string s1, s2;
    cin >>p;
    while(p --) cin >>s1; // 权限种类没用，所以不存
    cin >>r;
    while(r --) { // 角色
        cin >>s1 >>s;
        while(s --) {
            cin >>s2;
            pair<string, int> p = split(s2);
            if(role[s1].count(p.first) != 0) role[s1][p.first] = max(role[s1][p.first], p.second); // 取最大
            else role[s1].insert(p);
        }
    }
    cin >>u;
    while(u --) { // 用户
        cin >>s1 >>s;
        while(s --) {
            cin >>s2;
            for(auto p : role[s2]) { // 该角色所有权限
                if(user.count(s1) !=0 && user[s1].count(p.first) != 0) user[s1][p.first] = max(p.second, user[s1][p.first]); // 取大者
                else user[s1].insert(p);
            }
        }
    }
    cin >>q;
    while(q --) { // 查询
        cin >>s1 >>s2;
        pair<string, int> p = split(s2);
        if(user.count(s1) == 0 || user[s1].count(p.first) == 0 || user[s1][p.first] < p.second) printf("false\n");
        else {
            if(p.second == -1 && user[s1][p.first] != -1) printf("%d\n", user[s1][p.first]);
            else printf("true\n");
        }
    }
    return 0;
}