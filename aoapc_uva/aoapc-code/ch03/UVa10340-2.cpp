#include<bits/stdc++.h>
using namespace std;
string s, t;
int main() {
    while(cin >>s && cin >>t) {
        bool isSub = false; // 记录是否为子序列
        int i = 0, j = 0; // 双指针
        while (i < s.size() && j < t.size()) { // 以s为参照，遍历s，t
            if (s[i] == t[j]) { // 找到相等
                if (i == s.size() - 1) {
                    isSub = true;
                    break;
                }
                i ++; j ++;
            }
            while (j < t.size() && s[i] != t[j]) j ++;
        }
        printf("%s\n", isSub ? "Yes" : "No");
    }
    return 0;
}