#include<bits/stdc++.h>
using namespace std;
int n, ans;
bool flag = true, flag2 = false;
string s;
int main() {
    scanf("%d", &n);
    getchar();
    while(n --) {
        cin >>s;
        ans = s.size(); // 默认结果
        flag2 = false;
        for (int i = 1; i <= s.size() / 2; i ++) { // 枚举所有可能长度 
            if (s.size() % i == 0) {
                flag = true;
                for (int j = i; j <= s.size() - i; j += i) { // 比较长度为i的所有子串是否相同
                    if (s.substr(0, i) != s.substr(j, i)) {
                        flag = false;
                        break;
                    }
                }
                if (flag) { // 找到符合的周期串长度
                    ans = i;
                    flag2 = true;
                }
            }
            if (flag2) break;
        }
        printf("%d%s", ans, (n == 0) ? "\n" : "\n\n"); // 相邻两个输出间需输出空行，最后一行不用
    }
    return 0;
}