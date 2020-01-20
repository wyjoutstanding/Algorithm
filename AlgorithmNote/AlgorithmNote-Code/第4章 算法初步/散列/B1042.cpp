/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 10:17:52
 * @LastEditTime: 2019-07-28 10:33:05
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    getline(cin, s); //有空格
    int hashTable[128] = {0};
    for(int i = 0; i < s.size(); i++) {
        char t = s[i];
        if(t >= 'A' && t <= 'Z') {
            t = t + ('a' - 'A'); //大写转为小写
            s[i] = t;
        }
        hashTable[t] ++;
    }
    // 找字母频率最大，不唯一找字典序最小
    char ans = 'z'; //最大的字母
    int cnt = -1; //记录最大次数
    for(int i = 0; i < s.size(); i++) {
        char t = s[i];
        if(t >= 'a' && t <= 'z') {
            if((cnt < hashTable[t]) || (cnt == hashTable[t] && ans > t)) {
                cnt = hashTable[t];
                ans = t;
            }
        }
    }
    cout <<ans <<" " <<cnt;
    return 0;
}