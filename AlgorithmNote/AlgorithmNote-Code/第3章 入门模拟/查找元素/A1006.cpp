#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >>n;
    string sit_name, sot_name;  //开门、关门名字
    string sit = "24:59:59", sot = "00:00:00";    //开门、关门时间
    string tname, tit, tot; //从键盘读入
    for(int i = 0; i < n; i++) {
        cin >>tname >>tit >>tot;
        if(sit >= tit) {    //最小
            sit = tit;
            sit_name = tname;
        }
        if(sot <= tot) {    //最大
            sot = tot;
            sot_name = tname;
        }
    }
    cout <<sit_name <<" " <<sot_name;
    return 0;
}