#include <bits/stdc++.h>
using namespace std;
int main() {
    string s1;
    cin >>s1;
    int sum = 0;
    // 计算总和
    for(int i = 0; i < s1.length(); i++) {
        sum += (s1[i] - '0');
    }
    // 提取每一位，栈保存，便于输出；do...while无需考虑特例0
    stack<int> s;
    do {
        s.push(sum % 10);
        sum /= 10;
    }while(sum != 0);
    // 输出，转换数组简化代码；输出末尾无需多余空格
    string change[10] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    int len = s.size();
    for(int i = 0; i < len - 1; i++) {
        cout <<change[s.top()] <<" ";
        s.pop();
    }
    cout <<change[s.top()];
    return 0;
}