#include <bits/stdc++.h>
using namespace std;
int main() {
    int rgb[3]; //表示r,g,b
    cin >>rgb[0] >>rgb[1] >>rgb[2];
    char tag[14] = {'0','1','2','3','4','5','6','7','8','9','A','B','C'}; //统一输出
    cout <<"#";
    // 遍历r,g,b
    for(int i = 0; i < 3; i++) {
        stack<int> s;
        // 进制转换
        do {
            s.push(rgb[i] % 13);
            rgb[i] /= 13;
        }while(rgb[i] != 0);
        // 输出：仅有1位补0
        if(s.size() == 1) s.push(0);//补0
        while(!s.empty()) {
            cout <<tag[s.top()];
            s.pop();
        }
    }
    return 0;
}