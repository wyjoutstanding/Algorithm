#include<bits/stdc++.h>
using namespace std;
int a, b, i, f, ans = 0, cnt = 0;
string s, si, sf; // 整数和小数部分
map<int, int> mp; // 除数和对应下标
int main() {
    while(scanf("%d %d", &a, &b) == 2) {
        if (cnt++ != 0) printf("\n");
        printf("%d/%d = ", a, b);
        si = to_string(a / b); // 整数部分
        printf("%s.", si.c_str());
        a = a % b;
        int pre = 0, now = 0;
        s.clear(); sf.clear(); mp.clear();
        while(true) {
            bool flag = false;
            while(a != 0 && a < b) {
                a *= 10;
                now ++;
                sf += "0";
                flag = true;
                pre = now - 1;
            }
            if(flag) sf.pop_back();
            // printf("\na:%d a/b:%d a\%b:%d pre:%d now:%d\n", a, a/b, a%b, pre, now);
            if (mp.find(a) == mp.end()) { // 不存在
                mp.insert({a,pre});
                // if (flag) mp.insert({a,now});
                // else mp.insert({a,pre});
                // if (now != 0) sf += string(now-pre-1, '0') + to_string(a / b);
                if (now != 0) {
                    sf += to_string(a / b);
                    // now ++;
                }
                pre = now;
                a = a % b;
                if (a == 0) { // 整除/有限小数位
                    s = sf + "(0)";
                    ans = 1;
                }
            }
            else {
                // ans = pre - mp[a]; // 循环节长度
                ans = now - mp[a]; // 循环节长度
                if (pre > 50) {
                    s = sf.substr(0, mp[a]) + "(" + sf.substr(mp[a], 50 - mp[a]) + "...)";
                }
                else {
                    s = sf.substr(0, mp[a]) + "(" + sf.substr(mp[a], ans) + ")";
                }
                // printf("%s")
                // cout <<s <<endl <<ans<<endl;
                // break;
            }
            if (!s.empty()) {
                printf("%s\n   %d = number of digits in repeating cycle\n", s.c_str(), ans);
                // cout <<s <<endl<<ans<<endl;
                break;
            }
        }

    }
    
    return 0;
}