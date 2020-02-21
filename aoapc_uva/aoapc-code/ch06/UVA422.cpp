#include<bits/stdc++.h>
using namespace std;
int n, a, b;
char ch;
map<char, pair<int,int> > mp; // 矩阵->（行数，列数）
int simu(string s) { // 模拟相乘过程，错误返回-1，否则返回次数
    int ans = 0;
    stack<pair<int,int> > stk; // 矩阵栈，第一二维
    bool isErr=false; // 标记是否有错误
    for (auto c : s) {
        if (isalpha(c)) stk.push(mp[c]); // 矩阵
        if (c == ')') { // 出栈计算
            auto p1 = stk.top(); stk.pop();
            auto p2 = stk.top(); stk.pop();
            if (p2.second != p1.first) { // 错误
                isErr = true;
                break;
            }
            ans += p2.first*p2.second*p1.second; // 运算次数
            stk.push({p2.first, p1.second}); // 重新压入
        }
    }
    return ans = (isErr) ? -1 : ans;
}
int main() {
    scanf("%d", &n);
    while (n --) {
        getchar();
        scanf("%c %d %d", &ch, &a, &b);
        mp[ch] = {a,b};
    }
    string s;
    while (cin >>s) {
        int ans = simu(s);
        if (ans == -1) puts("error");
        else printf("%d\n", ans);
    }
    return 0;
}