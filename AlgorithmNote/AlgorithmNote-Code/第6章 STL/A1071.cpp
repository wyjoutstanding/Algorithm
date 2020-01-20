/*
 * @Author: wuyangjun
 * @Date: 2019-08-08 13:06:40
 * @LastEditTime: 2019-08-08 13:44:19
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
// 判断c是否为数字字母表中的一员
bool judge(char c) {
    if(c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') return true;
    else return false;
         
} 
int main() {
    string s;
    getline(cin, s);
    map<string, int> mp;
    string t;
    for(int i = 0; i < s.size(); i ++) {
        char c = s[i];
        if(judge(c)) {
            if(c >= 'A' && c <= 'Z') c = c + ('a' - 'A'); //大写转小写
            t.push_back(c);
        }
        if(!judge(c) || i == s.size() - 1) { //遇到不合法字符||最后一个需处理t
            if(t.empty()) continue; //若t为空，继续循环
            if(mp.count(t) == 0) mp[t] = 0; //初始化
            mp[t] ++;
            t.clear(); //清空
        }
    }
    string ans;
    int maxCnt = -1;
    // map自动有序，找最大值，若有多对也是取字典序小者
    for(auto p : mp) {
        if(maxCnt < p.second) {
            ans = p.first;
            maxCnt = p.second;
        }
    }
    cout <<ans <<" " <<maxCnt <<endl;
    return 0;
}