/*
 * @Author: wuyangjun
 * @Date: 2019-08-30 22:46:59
 * @LastEditTime: 2019-09-03 15:44:09
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
vector<pair<string, regex> > rules; // 规则名字name->正则表达式
vector<vector<int> > types; // 每条规则对应的参数类型；<int>:1 ; 其它为0
vector<pair<regex, string> > trans = {{regex("<int>"), "([\\d]+)"}, {regex("<str>"), "([^/]+)"}, {regex("<path>"), "(.+)"}};
int n, m;
void getRules() {
    scanf("%d %d", &n, &m);
    string name, s;
    for(int i = 0; i < n; i ++) {
        cin >>s >>name;
        // 保存每个分割点类型
        stringstream input(s.substr(1));
        vector<int> type;
        string tmp;
        while(getline(input, tmp, '/')) {
            if(tmp == "<int>") type.push_back(1);
            else if(tmp == "<str>" || tmp == "<path>") type.push_back(0);
        }
        types.push_back(type);
        // 参数替换为相应的正则表达式字符串
        for(auto p : trans) {
            s = regex_replace(s, p.first, p.second); // 返回被替换的结果 
        }
        rules.push_back({name, regex(s)}); // 构造新的正则表达式
    }
}
void query(string s) {
    smatch res;
    for(int i = 0; i < rules.size(); i ++) {
        if(regex_match(s, res, rules[i].second)) {
            cout <<rules[i].first; // name
            for(int j = 1; j <= res.size(); j ++) {
                if(res.size() == 1) break; // 无参数
                cout <<" ";
                string tmp = res.str(j);
                if(types[i][j-1] == 1) { // 去除前导0
                    int idx = tmp.find_first_not_of('0');
                    printf("%s", (idx == string::npos) ? "0" : tmp.substr(idx).c_str()); // 考虑全零特例：000000
                }
                else cout <<tmp; // 直接输出，path是根据输入原样输出，因此无需考虑最后的/
            }
            cout <<endl;
            return; // 直接返回
        }
    }
    cout <<"404" <<endl;
}
int main() {
    getRules();
    for(int i = 0; i < m; i ++) {
        string s;
        cin >>s;
        query(s);
    }
    return 0;
}