#include<bits/stdc++.h>
using namespace std;
int T;
vector<string> buf; // 存储输入的树
void dfs(int r, int c) { // 递归打印以buf(r,c)为根的子树
    printf("%c", buf[r][c]);
    if (r < buf.size()-1 && buf[r+1][c] == '|') { // 有孩子
        putchar('('); int l=c;
        while (buf[r+2][l] == '-') l--; // 查找--的左边界
        for (int i=l+1; i < buf[r+2].size() && buf[r+2][i] == '-'; i ++) {
            if (i < buf[r+3].size() && buf[r+3][i] != ' ') dfs(r+3, i); // 注意r+3的有效范围判断
        }
        putchar(')');
    }
    else printf("()");
}
int main() {
    scanf("%d", &T); getchar(); // 吸收多余换行
    string s;
    while (T --) {
        buf.clear();
        while (getline(cin, s) && s != "#") buf.push_back(s); // 以数组存储树
        putchar('(');
        for (int i=0; !buf.empty() && i < buf[0].size(); i ++) 
            if (buf[0][i] != ' ') {dfs(0,i); break;} // 找到根
        puts(")");
    }
    return 0;
}