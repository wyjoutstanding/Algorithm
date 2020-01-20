/*
 * @Author: wuyangjun
 * @Date: 2019-09-13 18:46:18
 * @LastEditTime: 2019-09-13 19:23:38
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
map<char, int> level = {{'#', 1}, {'+', 2}, {'-', 2}, {'x', 3}, {'/', 3}}; // 运算符优先级
int calculate(int a, int b, char opt) { // 计算a opt b的值
    int ret = 0;
    switch(opt) {
        case '+' : ret = a + b; break;
        case '-' : ret = b - a; break; // 反向
        case 'x' : ret = a * b; break;
        case '/' : ret = b / a; break; // 反向
    }
    return ret;
}
int solve(string& s) { // 计算表达式
    s += "#";
    stack<int> opd; // 操作数栈
    stack<char> opt; // 操作数栈
    opt.push('#'); // 操作符两端加上#，作为开始和结束标志
    for(int i = 0; i < s.size(); i ++) {
        if(isdigit(s[i])) opd.push(s[i] - '0'); // 操作数，直接入栈
        else { // 操作符
            while(!opt.empty() && level[s[i]] <= level[opt.top()]) { // 将优先级不高于s[i]的操作符弹出做运算
                if(s[i] == '#' && opt.top() == '#') break; // 特例，直接退出
                int a, b;
                a = opd.top(); opd.pop(); // 弹出两个操作数
                b = opd.top(); opd.pop();
                opd.push(calculate(a, b, opt.top())); // 压入计算结果
                opt.pop(); // 弹出操作符
            }
            opt.push(s[i]); // 当前符号压入符号栈
        }
    }
    return opd.top();
}
int main() {
    int n;
    scanf("%d", &n);
    string s;
    for(int i = 0; i < n; i ++) {
        cin >>s;
        printf("%s\n", (solve(s) == 24) ? "Yes" : "No");
    }
    return 0;
}