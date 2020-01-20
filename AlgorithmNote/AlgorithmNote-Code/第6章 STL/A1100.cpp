/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 22:06:03
 * @LastEditTime: 2019-08-07 23:15:31
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
string d[2][13] = {
    {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec"}, //第一位
    {"x", "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"} //第二位
};
map<string, int> mp[2]; 
// 字符串->数字
void initMap() {
    for(int i = 0; i < 2; i ++) {
        for(int j = 0; j < 13; j ++) {
            mp[i][d[i][j]] = j;
        }
    }
    
}
// 地球->火星：10->13->字符串
void EarthToMars(string s) {
    stringstream input(s); 
    int n;
    input >>n; //利用流转换为数值
    if(n >= 13) cout <<d[1][n / 13];
    if(n >= 13 && n % 13 != 0) cout <<" "; //注意空格输出时机
    if(n == 0 || n % 13 != 0) cout <<d[0][n % 13]; //13的整倍数无需输出低位
    cout <<endl;
}
// 火星->地球：字符串->13->10
void MarsToEarth(string s) {
    stringstream input(s);
    string tmp[2], t;
    int sum = 0, cnt = 0;
    // 位数
    while(input >>t) {
        tmp[cnt ++] = t;
    }
    // 2位，正常运算
    if(cnt == 2) {
        sum = mp[1][tmp[0]] * 13 + mp[0][tmp[1]];
    }
    // 1位，需判断是否为高位
    else {
        if(mp[0].count(tmp[0]) == 0) sum = mp[1][tmp[0]] * 13;
        else sum = mp[0][tmp[0]];
    }
    cout <<sum <<endl;
}
int main() {
    initMap(); // 别忘了调用
    int n;
    scanf("%d", &n);
    getchar(); //吸收多余空格
    string s;
    for(int i = 0; i < n; i ++) {
        getline(cin, s);
        if(s[0] >= '0' && s[0] <= '9') EarthToMars(s);
        else MarsToEarth(s);
    }
    return 0;
}