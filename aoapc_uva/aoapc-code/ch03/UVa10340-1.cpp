#include<bits/stdc++.h>
using namespace std;
string s, t;
int main() {
    while(cin >>s >>t) {
        int i = 0;
        for (auto ch : t) { // 以t为参照，依次比较
            if (ch == s[i]) i ++;
        }
        printf("%s\n", (i == s.size()) ? "Yes" : "No");
    }
    return 0;
}