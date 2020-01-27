#include<bits/stdc++.h>
using namespace std;
int main() {
    char ch;
    int cnt = 0; // 控制左右括号 (:0  ):1
    while(scanf("%c", &ch) != EOF) { // 两种输入均可
    // while((ch = getchar()) != EOF) {
        if (ch == '"') {
            if (cnt == 0) {
                printf("``");
                cnt = 1;
            }
            else {
                printf("''");
                cnt = 0;
            }
        } 
        else printf("%c", ch);
    }
    return 0;
}