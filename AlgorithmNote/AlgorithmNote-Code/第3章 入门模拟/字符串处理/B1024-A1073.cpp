#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >>s;
    char sign1, sign2;
    // 整体正负号
    sign1 = s[0];
    s = s.substr(1, s.length() - 1); //去除负号
    stringstream input1(s);
    string tmp, interger, frac, exp;
    // 取数值部分
    getline(input1, tmp, 'E');
    stringstream input2(tmp);
    // 整数部分
    getline(input2, interger, '.');
    // 小数部分
    getline(input2, frac, '.');
    // 指数部分
    getline(input1, exp, 'E');
    // 指数正负号
    sign2 = exp[0];
    int exp_dec = stoi(exp, 0, 10);//指数转换为数值
    exp_dec = abs(exp_dec);//取绝对值
    // 负号输出
    if(sign1 == '-') cout <<sign1;
    // 特例，exp=0，直接输出
    if(exp_dec == 0) {
        cout <<interger <<"." <<frac;
        return 0;
    }
    // 正指数
    if(sign2 == '+') {
        cout <<interger;
        if(frac.size() > exp_dec) {
            for(int i = 0; i < frac.size(); i++) {
                if(i == exp_dec - 1) cout <<frac[i] <<".";
                else cout <<frac[i];
            }
        }
        else {//等于的情况必须和 < 放一块，否则可能存在末尾多余[.]。例如 +1.23400E+05
            cout <<frac;
            for(int i = 0; i < exp_dec - frac.size(); i++) {
                cout <<"0";
            }
        }
    }
    // 负指数
    else {
        for(int i = 0; i < exp_dec; i++) {
            if(i == 0) cout <<"0.";
            else cout <<"0";
        }
        cout <<interger <<frac;
    }
    return 0;
}