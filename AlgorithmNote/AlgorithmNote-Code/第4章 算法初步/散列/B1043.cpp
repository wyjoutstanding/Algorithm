/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 10:53:30
 * @LastEditTime: 2019-07-28 11:01:00
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    getline(cin, s);
    char change[6] = {'P', 'A', 'T', 'e', 's', 't'};
    int hashTable[128] = {0};
    for(int i = 0; i < s.size(); i++) {
        char t = s[i];
        // 仅统计6个字符
        for(int j = 0; j < 6; j++) {
            if(change[j] == t) {
                hashTable[t] ++;
                break;
            }
        }
    }
    while(true) {
        int isPrint = false;
        // 6个字符输出为1轮
        for(int i = 0; i < 6; i++) {
            char t = change[i];
            if(hashTable[t] != 0) {
                cout <<t;
                hashTable[t] --;
                isPrint = true;
            }
        }
        if(!isPrint) break; //打印完毕
    }
    return 0;
}