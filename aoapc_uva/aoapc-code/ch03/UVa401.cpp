#include<bits/stdc++.h>
using namespace std;
string rev = "A   3  HIL JM O   2TUVWXY51SE Z  8 ", s; // 镜像哈希串
char *msg[] = {" -- is not a palindrome.", " -- is a regular palindrome.", " -- is a mirrored string.", " -- is a mirrored palindrome."};
char toRev(char ch) {
    if (isalpha(ch)) return rev[ch - 'A'];
    else return rev[ch - '1' + 26];
}
int main() {
    int p, m;
    while(getline(cin, s) && !s.empty()) {
        p = 1; m = 1; // 分别表示回文和镜像串
        for (int i = 0; i <= s.size() / 2; i ++) {
            if (s[i] != s[s.size() - i - 1]) p = 0; // 回文判断
            if (toRev(s[i]) != s[s.size() - i -1]) m = 0; // 镜像为空直接不符合！！！
        }
        printf("%s%s\n\n", s.c_str(), msg[m*2+p]); // 多一个空行！！！
    }
    return 0;
}