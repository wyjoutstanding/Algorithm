/*
 * @Author: wuyangjun
 * @Date: 2019-08-30 10:12:37
 * @LastEditTime: 2019-09-02 08:53:23
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct Rule { // URL规则
    string name; // 名字
    vector<string> r; // 存储分割后的URL和参数
    vector<int> type; // 对应每个字段的类型：0：URL 1：整数 2：字符串 3：路径
};
vector<Rule> rules;
vector<bool> endExt; // 记录每条规则末尾是否存在/。true：存在
struct Query { // 单条查询URL
    vector<string> items; // 每个条目
    vector<int> type; // 可表示的最小类型：1：整数 2：字符串
    bool extEnd; // 判断末尾是否有/
    Query() {extEnd = false;}
};
int n, m;
void print() {
    for(auto p : rules) {
        cout <<"name===" <<p.name <<endl;
        for(int i = 0; i < p.r.size(); i ++) {
            cout <<p.r[i] <<" " <<p.type[i] <<endExt[i] <<endl;
        }
    }
}
void print2(Query q) {
    // for(auto p : q) {
        cout <<"Query:END===" <<q.extEnd <<endl;
        for(int i = 0; i < q.type.size(); i ++) {
            cout <<q.items[i] <<" " <<q.type[i] <<endl;
        }
    // }
}
void getRules() {
    scanf("%d %d", &n, &m);
    string s, tmp;
    for(int i = 0; i < n; i ++) {
        Rule r;
        cin >>s >>r.name;
        if(s.back() == '/') endExt.push_back(true); // 结尾是否有/，巨坑
        else endExt.push_back(false);
        stringstream input(s.substr(1)); // 去除第一个/
        while(getline(input, tmp, '/')) {
            // 类型选择
            int type = 0; // 默认为URL
            if(tmp == "<int>") type = 1;
            else if(tmp == "<str>") type = 2;
            else if(tmp == "<path>") type = 3;
            r.type.push_back(type);
            r.r.push_back(tmp);
        }
        rules.push_back(r);
    }
}
// 判断字符串是否全为数字
bool isNumber(string s) {
    for(auto p : s) if(isdigit(p) == 0) return false;
    return true;
}
// 分割单条查询
Query getQuery(string s) {
    Query ret;
    if(s.back() == '/') ret.extEnd = true; // 结尾是否有/
    string tmp;
    stringstream input(s.substr(1)); // 去开头/
    while(getline(input, tmp, '/')) { // 分割
        int type = 2; // 默认为<str>
        if(isNumber(tmp)) type = 1; // 升级为<int>
        ret.type.push_back(type);
        ret.items.push_back(tmp);
    }
    return ret;
}
// 打印结果
void printAns(vector<int>& ans, Rule& r, Query& q) {
    for(int i = 0; i < ans.size(); i ++) {
        int idx = ans[i];
        cout <<" ";
        if(r.type[idx] == 1) { // 整数去前导0
            string tmp = q.items[idx];
            int pos = tmp.find_first_not_of('0');
            printf("%s", (pos == string::npos) ? "0" : tmp.substr(pos).c_str()); // 特例全0：00000
            // cout <<q.items[idx].substr(q.items[idx].find_first_not_of('0')); // 
        }
        else cout <<q.items[idx]; // 字符串
    }
}
// 处理单条查询
void query(string& s) {
    Query q = getQuery(s);
    // cout <<"=="<<s<<endl;
    int ridx = -1;
    for(auto r : rules) { // 遍历所有规则
        ridx ++; // 记录当前规则的下标
        vector<int> ans; // 存储匹配的参数下标
        for(int i = 0; i < r.r.size(); i ++) {
            if(i == q.type.size()) break; // query太短
            if(r.type[i] == 3) { // 路径，直接输出所有参数
                cout <<r.name;
                // TODO ans输出
                printAns(ans, r, q);
                printf(" ");
                for(int j = i; j < q.type.size(); j ++) { // 输出剩余参数
                    if(j != q.type.size() - 1) cout <<q.items[j] <<"/";
                    else cout <<q.items[j];
                }
                if(q.extEnd) cout <<"/";
                cout <<endl;
                return; // 结束查询
            } else if(r.type[i] == 0) { // URL
                if(r.r[i] != q.items[i]) break;
                // else ans.push_back(i);
            } else if(r.type[i] == 1) { // 整数<int>
                if(q.type[i] == 1) ans.push_back(i);
                else break;
            } else ans.push_back(i); // <str>
            if(i == r.r.size() - 1 && i < q.type.size() - 1) break; // query太长
            if(i == r.r.size() - 1 && (q.extEnd == endExt[ridx])) { // 当前规则匹配成功且url与规则末尾/同在
                cout << r.name;
                printAns(ans, r, q);
                cout <<endl;
                return;
            }
        }
    }
    cout <<"404" <<endl;
}
int main() {
    getRules();
    print();
    string s;
    for(int cnt = 0; cnt < m; cnt ++) {
        cin >>s;
        query(s);
    }
    return 0;
}