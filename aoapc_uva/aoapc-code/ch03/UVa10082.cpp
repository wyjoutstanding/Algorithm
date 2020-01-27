#include<bits/stdc++.h>
using namespace std;
string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./", s;
int main() {
    while(getline(cin, s) && !s.empty()) {
        for (char ch : s) {
            if (ch == ' ') printf(" ");
            else printf("%c", keyboard[keyboard.find(ch)-1]);
        }
        printf("\n"); // 换行记录
    }
    return 0;
}