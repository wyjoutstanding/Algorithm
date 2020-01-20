#include <bits/stdc++.h>
using namespace std;
int main() {
    string day[7] = {"MON","TUE","WED","THU","FRI","SAT","SUN"};
    string s[4];
    cin >>s[0] >>s[1] >>s[2] >> s[3];
    // 遍历两组
    for(int i = 0; i < 4; i += 2) {
        int cnt = 1;//记录第一组的第cnt次
        int len = (s[i].length() < s[i+1].length()) ? s[i].length() : s[i+1].length();//取较短者
        for(int j = 0; j < len; j++) {//遍历比较字符串
            char ch = s[i][j];
            // 第一组:i=0 => DAY,HH
            if(i == 0) {
                // 第一次命中：大写字母
                if(cnt == 1) {
                    if(ch == s[i+1][j] && (ch >= 'A' && ch <= 'G')) {//不可以是Z，必须指定A~G，否则出现Z时就会输出
                        cnt++;
                        cout <<day[ch - 'A'] <<" ";
                    }
                }
                // 第二次命中：0~9 ，A~N
                else if(ch == s[i+1][j]) {
                    // 0~9 => 补0
                    if(ch >= '0' && ch <= '9') { 
                        cout <<'0' <<ch <<":";// 不足补0
                        break;//不退出重复的会输出
                    }
                    // A~N => 10~23
                    else if(ch >= 'A' && ch <= 'N') { 
                        cout <<(ch - 'A' + 1 + 9) <<":";
                        break;//不退出重复的会输出
                    }
                }
            }
            // 第二组:i = 2 =>MM
            else if(ch == s[i+1][j] && ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))) {//第二组：a~z,A~Z
                if(j < 10) cout <<'0';// 不足补0
                cout <<j;
                break;//输出立即退出，避免后续相等的干扰
            }
        }
    }
    return 0;
}