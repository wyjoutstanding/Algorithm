#include<bits/stdc++.h>
using namespace std;
string s, st;
vector<string> lines[1010]; // 每一行的单词
int row=0, maxcol[1010] = {0}; // 行号，每列单词最长值
int main() {
    while (getline(cin ,s)) {
        stringstream input(s);
        while (input >>st) { // 空格分割
            maxcol[lines[row].size()] = max(maxcol[lines[row].size()], (int)st.size()); // 取最大值
            lines[row].push_back(st); // 保存单词
        }
        row ++; // 行号
    }
    for (int i = 0; i < row; i ++) { // 按行遍历输出
        for (int j = 0; j < lines[i].size(); j ++) {
            st = lines[i][j]; 
            if (j != lines[i].size()-1) st += string(maxcol[j]-st.size()+1, ' '); // 补空格
            printf("%s", st.c_str());
        }
        puts("");
    }
    return 0;
}