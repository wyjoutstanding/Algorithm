/*
 * @Author: wuyangjun
 * @Date: 2019-08-07 20:09:27
 * @LastEditTime: 2019-08-07 21:16:07
 * @Github: https://github.com/wyjoutstanding
 */
#include <bits/stdc++.h>
using namespace std;
struct ScienceNum {
    string frac;
    int exp; //指数
};
ScienceNum getScienceNum(string s, int n) {
    ScienceNum res;
    // 去除多余前导0，并且至少保留1位
    while(s.size() > 1 && s[0] == '0' && s[1] != '.') s.erase(s.begin());
    // xx.xx / xx
    if(s[0] != '0') {
        int pos = s.find('.');
        res.exp = (pos == -1) ? s.size() : pos;
        for(auto p : s) {
            if(p != '.' && res.frac.size() < n) res.frac.push_back(p);
        }
    }
    // 0.xx
    else {
        res.exp = 0;
        int i;
        for(i = 2; i < s.size(); i ++) {
            if(s[i] != '0') break;
            res.exp --;
        }
        if(i == s.size()) res.exp = 0; //0.00特判
        while(i < s.size() && res.frac.size() < n) res.frac.push_back(s[i++]);
    }
    // 不足n为向后补0
    while(res.frac.size() < n) res.frac.push_back('0');
    return res;
}
void print(ScienceNum a, int n) {
    printf("0.");
    cout <<a.frac;
    printf("*10^%d", a.exp);
}
// 比较两个计数法是否相同
bool cmp(ScienceNum a, ScienceNum b) {
    return a.exp == b.exp && a.frac == b.frac;
}
int main() {
    int n;
    scanf("%d", &n);
    string a, b;
    cin >>a >>b;
    ScienceNum sa = getScienceNum(a, n);
    ScienceNum sb = getScienceNum(b, n);
    // 输出
    if(cmp(sa, sb)) {
        printf("YES ");
        print(sa, n);
    }
    else {
        printf("NO ");
        print(sa, n);
        printf(" ");
        print(sb, n);
    }
    printf("\n");
    return 0;
}