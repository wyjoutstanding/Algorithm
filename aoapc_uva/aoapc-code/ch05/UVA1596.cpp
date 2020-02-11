#include<bits/stdc++.h>
using namespace std;
map<string, int> arrlen; // 数组名->长度
map<string, map<int,int> > arr; // 数组名->下标->值（模拟二维数组）
string s, sl, sr;
pair<string, string> getNameExpr(string s) { // 获取数组名和下标
    int i = s.find('[');
    return {s.substr(0, i), s.substr(i+1, s.size()-i-2)};
}
int eval(string s) { // 对s进行求值，若有bug返回-1，否则返回正确值
    int idx;
    stack<string> stk; // 存储数组名
    string st = s;
    while (!isdigit(st[0])) { // 依次分割提取数组表达式
        pair<string,string> pr = getNameExpr(st);
        stk.push(pr.first);
        st = pr.second;
    }
    idx = stoi(st); // 最内层下标
    while (!stk.empty()) { // 出栈求值
        st = stk.top();
        if (arrlen[st] <= idx || arr[st].find(idx) == arr[st].end()) break; // 下标溢出/未赋值
        stk.pop();
        idx = arr[st][idx]; // 新的长度
    }
    return stk.empty() ? idx : -1; // -1表示有bug
}
int main() {
    bool isOver = false; // 判断是否结束读取测试用例
    while (!isOver) {
        arrlen.clear(); arr.clear(); isOver=true;// 初始化
        int line=0; bool isBug=false;
        while (cin >>s && s[0] != '.') {
            if (isBug) continue; // 找到bug，继续读完即可
            int i = s.find('='); isOver=false; line ++;
            if (i == string::npos) { // 定义表达式
                pair<string,string> pr = getNameExpr(s);
                arrlen[pr.first] = stoi(pr.second); // 数组长度
            }
            else { // 赋值表达式
                sl = s.substr(0,i); sr = s.substr(i+1); // 左右表达式
                int rval = eval(sr); // 右值
                if (rval != -1) { // 右部表达式合法
                    pair<string,string> pr = getNameExpr(sl);
                    int idx = eval(pr.second);
                    if (idx != -1 && idx < arrlen[pr.first]) arr[pr.first][idx] = rval; // 下标表达式非法/溢出
                    else isBug = true; // 出现bug
                }
                else isBug = true;
            }
        }
        if (!isOver) printf("%d\n", isBug ? line : 0); // 未结束均需输出
    }
    return 0;
}