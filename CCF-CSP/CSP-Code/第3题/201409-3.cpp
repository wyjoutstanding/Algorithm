/*
 * @Author: wuyangjun
 * @Date: 2019-09-07 21:37:04
 * @LastEditTime: 2019-09-07 23:17:37
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
int main() {
    string dist, tmp, s;
    int flag, n;
    cin >>dist >>flag >>n;
    // if(flag == 0) transform(dist.begin(), dist.end(), dist.begin(), [](char c) {return tolower(c);}); //转为小写
    if(flag == 0) transform(dist.begin(), dist.end(), dist.begin(), ::tolower); //转为小写
    while(n --) {
        cin >>s;
        tmp = s;
        if(flag == 0) transform(tmp.begin(), tmp.end(), tmp.begin(), [](char c) {return tolower(c);}); //转为小写
        if(tmp.find(dist) != string::npos) printf("%s\n", s.c_str());
    }
    return 0;
}