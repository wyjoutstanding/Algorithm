#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >>s;
    // cout<<s <<" "<<"123";
    int hash[10] = {0}; //哈希计数
    for(int i = 0; i < s.size(); i++) {
        hash[s[i] - '0']++; //转换为整型
    }
    for(int i = 0; i < 10; i++) {
        if(hash[i] != 0) cout <<i <<":" <<hash[i] <<endl;
    }
    return 0;
}