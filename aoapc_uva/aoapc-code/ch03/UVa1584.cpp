#include<bits/stdc++.h>
using namespace std;
int main() {
    string str, ans, s;
    int n;
    cin >>n;
    while(n --) {
        cin >>str;
        ans = str;
        for (int i = 1; i < str.size(); i ++) { // 遍历每一种情况，i表示开始下标
            s = str.substr(i) + str.substr(0, i); // 拼接循环字符串
            ans = min(ans, s); // 取小，string类对<重载
        }
        cout <<ans <<endl;
    }
    return 0;
}