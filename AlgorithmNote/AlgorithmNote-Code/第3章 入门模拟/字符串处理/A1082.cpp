#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >>s;
    stack<string> res;
    // 正负号处理
    if(s[0] == '-') {
        s = s.substr(1, s.size() - 1);
        cout <<"Fu ";
    }
    reverse(s.begin(), s.end());
    string change[4] = {"","Shi", "Bai", "Qian"};
    string num_change[10] = {"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
    int len = s.size();
    // 0特別处理，顺便把一位的数字全处理了
    if(len == 1) {
        cout <<num_change[s[0] - '0'];
        return 0;
    }
    // 从个位开始遍历，4个为一个单元（个十百千），万和亿作为大单位
    for(int i = 0; i < len; i++) {
        // 万、亿处理
        if(i == 4) {
            bool isAllZero = true;
            // 特例：5~8位均为0，不需要单位Wan  eg.100001234
            for(int j = i; j < len && j < i + 4; j++) {
                if(s[j] != '0') {
                    isAllZero = false;
                    break;
                }
            }
            if(isAllZero == true) res.push(num_change[0]);
            else res.push("Wan");
        }
        else if(i == 8) res.push("Yi");
        // 单元处理（个十百千）：0的处理，当flag=0时才将遇到第一个的0压栈
        int flag = 1, j;
        for(j = i; j < len && j < i + 4; j++) {
            if(s[j] == '0'){//0特殊处理
                if(flag == 1) continue;
                else {
                    res.push(num_change[s[j] - '0']);//只需压入数字，无需单位  
                    flag = 1;
                }         
            }
            else {
                flag = 0;//遇到非零之后就可以记录0
                if(j % 4 != 0) res.push(change[j % 4]);//先压单位
                res.push(num_change[s[j] - '0']);
            }
        }
        i = j - 1;//下一个单元
    }
    // 输出
    len = res.size();
    for(int i = 0; i < len - 1; i++) {
        cout <<res.top() <<" ";
        res.pop();
    }
    cout <<res.top();

    return 0;
}