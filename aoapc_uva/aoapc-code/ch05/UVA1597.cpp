#include<bits/stdc++.h>
using namespace std;
int N, M;
string s, st, t1, t2;
map<string, vector<pair<int,int> > > mp; // 单词->(文章id,行号)
vector<string> doc[110]; // 文本
int main() {
    cin >>N; getchar(); // 吸收换行
    for (int i = 0; i < N; i ++) { // 所有文本 
        int line=0; // 行号
        while (getline(cin ,s) && s[0] != '*') {
            doc[i].push_back(s); // 文本i的第line行
            for (auto& ch : s) 
                if (!isalpha(ch)) ch = ' '; // 非字母全换为空格
                else ch = tolower(ch); // 字母均转为小写
            stringstream input(s); // 空格分割
            while (input >>s) mp[s].push_back({i, line}); // word所在文本编号和行号
            line ++; // 行号增加
        }
    }
    cin >>M; getchar();
    while (M --) { // 查询处理
        getline(cin, s); // 查询
        int i = s.find(' '), j = s.rfind(' '); // 从首，尾开始遇见的第一个空格位置
        set<pair<int,int> > out; // 输出集合
        if (i == string::npos) out.insert(mp[s].begin(), mp[s].end());  // term
        else { // 与或非
            if (s[0] == 'N') { // NOT
                t1 = s.substr(i+1);
                set<int> _set;
                for (int i = 0; i < N; i ++) _set.insert(i); // 所有文章id
                for (auto p : mp[t1]) _set.erase(p.first); // 删除包含t1的文章id
                for (auto p : _set) { // 输出整篇文章
                    for (auto line : doc[p]) cout <<line <<endl; // 打印不包含t1的所有整篇文章
                    if (p != *_set.rbegin()) cout <<"----------"<<endl; // 不同文章需间隔
                }
                if (_set.empty()) cout <<"Sorry, I found nothing.\n"; // 空处理
            }
            else { // AND,OR
                t1 = s.substr(0, i); // term1
                t2 = s.substr(j+1); // term2
                out.insert(mp[t1].begin(), mp[t1].end()); // 求并集 
                out.insert(mp[t2].begin(), mp[t2].end());
                if (j - i - 1 == 3) { // AND，求交集
                    set<int> set1, set2;
                    for (auto p : mp[t1]) set1.insert(p.first); // t1所在文本
                    for (auto p : mp[t2]) if (set1.find(p.first) != set1.end()) set2.insert(p.first); // 求交集文本
                    auto tmp = out; // 先备份，再删除；若边删边遍历会RE
                    for (auto p : tmp) if (set2.find(p.first) == set2.end()) out.erase(p); // 删除不相交的
                }
            }
        }
        int pre=-1; // 控制间隔输出
        if (s[0] != 'N') { // 非NOT语句统一输出
            for (auto p : out) {
                if (pre != -1 && pre != p.first) cout <<"----------"<<endl; // 两个不同文章之间
                pre = p.first;
                cout <<doc[p.first][p.second] <<endl;
            }
            if (out.empty()) cout <<"Sorry, I found nothing.\n";
        }
        cout <<"==========" <<endl;
    }
    return 0;
}