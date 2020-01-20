/*
 * @Author: wuyangjun
 * @Date: 2019-07-28 07:47:27
 * @LastEditTime: 2019-07-28 08:15:44
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string hide, input;
    getline(cin, hide); //可能为空行，必须这么读
    getline(cin, input);
    map<char, int> mp;
    bool flag = false; //是否为上档键
    if(hide.size() != 0) { //是否为空行
        for(int i = 0; i < hide.size(); i++) {
            char t = hide[i];
            // if(t == ',' || t == '.' || t == '-' || t == '+') flag = true;
            if(t == '+') flag = true; //只有+是上档键
            mp[t] = 1; //表示存在
        }
        bool isPrint = false; //判断是否有输出
        for(int i = 0; i < input.size(); i++) {
            char t = input[i];
            if(flag && (t >= 'A' && t <= 'Z')) continue; //上档键损坏大写不输出
            if(t >= 'a' && t <= 'z') t = t - ('a' - 'A'); //小写转为大写
            if(mp.count(t) == 0) { //可输出
                cout <<input[i]; //输出原来字符，可能为小写
                isPrint = true;
            }
        }
        if(!isPrint) cout <<endl;
    }     
    else cout <<input <<endl;
    return 0;
}