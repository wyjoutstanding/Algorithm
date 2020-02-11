#include<bits/stdc++.h>
using namespace std;
int T;
string sa, sb;
void getDict(map<string,string>& mp, string s) { // 分割得到字典
    for (auto& ch : s) // 将{},:替换为空格
        if (ch == '{' || ch == '}' || ch == ',' || ch == ':') ch = ' ';
    stringstream input(s);
    string sk, sv;
    while (input >>sk >>sv ) mp[sk] = sv; // stringstream以空格分割
}
void print(char mess, const set<string>& _set) { // 打印结果
    if (_set.empty()) return; // 空立刻返回
    cout <<mess;
    for (auto p : _set) printf("%s%s", p.c_str(), p == *_set.rbegin() ? "\n" : ",");
}
int main() {
    cin >>T;
    for (int i = 0; i < T; i ++) {
        cin >>sa >>sb;
        map<string,string> mpa, mpb; // 旧新字典
        getDict(mpa, sa); getDict(mpb, sb);
        set<string> del, chg, inc; // 删除，改变，增加
        for (auto p : mpa) { // 遍历旧字典
            if (mpb.find(p.first) == mpb.end()) del.insert(p.first); // 删除
            else { // 存在
                if (mpa[p.first] != mpb[p.first]) chg.insert(p.first); // 改变
                mpb.erase(p.first); // 删除mpa中存在的
            }
        }
        for (auto p : mpb) inc.insert(p.first); // 未被删除的就是增加的
        print('+', inc); print('-', del); print('*', chg); // 输出结果
        if (inc.empty() && del.empty() && chg.empty()) puts("No changes");
        puts(""); // 空行
    }
    return 0;
}