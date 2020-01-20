/*
 * @Author: wuyangjun
 * @Date: 2019-09-02 18:58:57
 * @LastEditTime: 2019-09-03 06:30:51
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
map<string, string> headTrans = {{"#", "1"}, {"##", "2"}, {"###", "3"}, {"####", "4"}, {"#####", "5"}, {"######", "6"}};
void solve(string& block) { // 处理一块
    if(!block.empty()) {
        // block = regex_replace(block, regex("_(.+)_"), "<em>$1</em>"); // 不可取10个测试点不过
        block = regex_replace(block, regex("_([^_]+)_"), "<em>$1</em>"); // 强调
        // block = regex_replace(block, regex("\\[(.+)\\]\\((.+)\\)"), "<a href=\"$2\">$1</a>"); // 1个点不过
        block = regex_replace(block, regex("\\[([^\\]]+)\\]\\(([^\\)]+)\\)"), "<a href=\"$2\">$1</a>"); //超链接
        block.erase(block.end() - 1); // 擦除最后的换行
        if(block[0] == '#') { // 标题
            for(auto mp : headTrans) {
                block = regex_replace(block, regex("^" + mp.first + " +(.+)$"), "<h"+mp.second+">$1</h"+mp.second+">\n");
            }
        }
        else if(block[0] == '*') { // 无序列表
            block = regex_replace(block, regex("\\* +(.+)"), "<li>$1</li>");
            block = "<ul>\n" + block + "\n</ul>\n";
        }
        else block = "<p>" + block + "</p>\n"; // 段落
        cout <<block;
        block.clear();
    }
}
int main() {
    string s, block;
    while(getline(cin, s)) {
        if(!s.empty()) block += (s + "\n");
        else solve(block);
    }
    solve(block); // 处理最后一块
    return 0;
}