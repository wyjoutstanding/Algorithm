#include <bits/stdc++.h>
using namespace std;
int main() {
    int N, b;
    cin >>N >>b;
    stack<int> s, ans;
    queue<int> q;
    // 除基取余法：栈和队列保存
    do {
        int t = N % b;
        s.push(t);
        q.push(t);
        N /= b;
    }while(N != 0);
    // 回文判断：栈和队列对比
    bool flag = true;
    ans = s;
    while(!s.empty()) {
        if(s.top() != q.front()) {
            flag = false;
            break;
        }
        s.pop();
        q.pop();
    }
    // 输出
    if(flag) cout <<"Yes" <<endl;
    else cout <<"No" <<endl;
    int len = ans.size();  //最后一个输出不许存在空格
    for(int i = 0; i < len - 1; i++) {
        cout <<ans.top() <<" ";
        ans.pop();
    }
    cout <<ans.top();
    return 0;
}