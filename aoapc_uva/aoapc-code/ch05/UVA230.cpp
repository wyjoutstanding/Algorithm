#include<bits/stdc++.h>
using namespace std;
struct Book {
    string aut, tit; // 作者，书名
    bool operator < (const Book& b) { // 排序使用，作者字典序小者优先，若相同，书名优先
        return aut < b.aut || (aut == b.aut && tit < b.tit);
    }
}book;
string s, st, op, tit;
vector<Book> bk; // 存书列表
map<string, int> mp; // 书名对应编号
int main() {
    while (getline(cin, s) && s[0] != 'E') {
        int i = s.find('"', 1); // 找到第二个引号位置
        book.tit = s.substr(1, i-1); // 书名
        book.aut = s.substr(i+5); // 作者
        bk.push_back(book);
    }
    sort(bk.begin(), bk.end()); // 排序，作者字典序小优先，若相同，书名字典序小者优先
    set<int> lib, ret; // 保存图书库存和还书集合
    for (int i = 0; i < bk.size(); i ++) {
        mp[bk[i].tit] = i; // 书名对应编号id
        lib.insert(i); // 图书库存
    }
    while (getline(cin, s) && s[0] != 'E') { // 借/还/显示操作处理
        if (s[0] == 'S') { // 显示输出
            for (auto r : ret) { // 遍历还书集合
                auto p = lib.find(r); // 当前书本所在位置
                printf("Put \"%s\" ", bk[r].tit.c_str());
                printf("%s\n", p == lib.begin() ? "first" : ("after \""+bk[*(--p)].tit+"\"").c_str());
            }
            puts("END"); ret.clear(); // 清空为下一次准备
            continue; // 继续读入
        }
        op = s.substr(0, 6); // 操作
        tit = s.substr(8, s.size()-8-1); // 书名
        if (op[0] == 'B') lib.erase(mp[tit]); // 借书，从lib删除
        else if (op[0] == 'R') { // 还书
            ret.insert(mp[tit]); // 加入还书集合
            lib.insert(mp[tit]); // 加入lib集合
        }
    }
    return 0;
}