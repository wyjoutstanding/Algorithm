#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b;
    cin >>a >>b;
    int sum = a + b;
    int sign = 0;
    if(sum < 0) {
        sign = 1;//1表示负数 
        sum = -sum;//取绝对值
    }
    else if(sum == 0) { //0特例单独判断
        cout <<0;
        return 0;
    }
    // 从低位到高位依次入栈，若3*i + 1位存在，将逗号入栈，如第4位存在，才先将逗号入栈，在将数字入栈
    stack<char> s; //字符存储，便于输出
    int cnt = 0;
    while(sum != 0) {
        if(cnt != 0 && cnt % 3 == 0) { //关键
            s.push(',');
        }
        s.push((sum % 10) + '0'); //数字 -> 字符
        cnt ++;
        sum /= 10;
    }
    // 输出
    if(sign == 1) cout <<'-';
    while(!s.empty()) {
        cout <<s.top();
        s.pop();
    }
    return 0;
}