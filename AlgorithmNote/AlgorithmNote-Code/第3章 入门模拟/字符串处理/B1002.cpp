#include <bits/stdc++.h>
using namespace std;
int main() {
    string py[10] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
    string s;
    cin >>s;
    int sum = 0;
    // 计算个位数字总和
    for(int i = 0; i < s.size(); i++) {
        sum += s[i] - '0';
    }
    // 低位到高位依次入栈
    stack<int> ans;
    do {
        ans.push(sum % 10);
        sum /= 10;
    }while(sum != 0);
    // 输出：末尾无需多余空格
    int cnt = ans.size();
    for(int i = 0; i < cnt - 1; i++) {
        cout <<py[ans.top()] <<" ";
        ans.pop();
    }
    cout <<py[ans.top()];
    return 0;
}