#include <bits/stdc++.h>
using namespace std;
int main() {
    string tmp;
    stack<string> s;
    getline(cin, tmp);//键盘读入
    stringstream input(tmp);//stringstream构造函数
    //分割，第三个参数为char型
    while(getline(input, tmp, ' ')) {
        s.push(tmp);
    }
    // 输出
    int len = s.size();
    for(int i = 0; i < len - 1; i++) {
        cout <<s.top() <<" ";
        s.pop();
    }
    cout <<s.top();
    return 0;
}