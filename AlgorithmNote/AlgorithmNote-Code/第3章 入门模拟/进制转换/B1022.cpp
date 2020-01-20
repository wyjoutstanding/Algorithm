#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b, d, n;
    cin >>a >>b >>d;
    n = a + b;
    if(n == 0) cout <<0;    //0直接输出
    else {  //非零用除基取余法，借用栈结构保存余数
        stack<int> res;
        while(n != 0) {
            res.push(n % d);
            n /= d;
        }
        while(!res.empty()) {   //输出
            cout <<res.top();   //先取栈顶，再pop
            res.pop();
        }
    }
    return 0;
}