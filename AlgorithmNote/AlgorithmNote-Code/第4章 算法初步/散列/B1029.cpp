/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 06:24:52
 * @LastEditTime: 2019-07-28 07:10:26
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string input, output;
    cin >>input >>output;
    // 记录输出字符串出现的每个字符（小写当大写存）
    map<char, int> mp;
    for(int i = 0; i < output.size(); i ++) {
        char ch = output[i];
        if(ch >= 'a' && ch <= 'z') ch = ch - ('a' - 'A'); //转换为大写
        mp[ch] = 1;
    }
    // 遍历输入字符串，将小写转为大写，判断输出是否存在相应字符，不在则输出，同时标记为1
    for(int i = 0; i < input.size(); i ++) {
        char ch = input[i];
        if(ch >= 'a' && ch <= 'z') ch = ch - ('a' - 'A'); //转换为大写
        // 非小写字母 && 实际字符串中没有该字符的需要输出
        if(mp.count(ch) == 0) {
                cout <<ch;
                mp[ch] = 1; //仅输出一次
        }
    }
    return 0;
}