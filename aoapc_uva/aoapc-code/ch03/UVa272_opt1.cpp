#include<bits/stdc++.h>
using namespace std;
int main() {
    char ch;
    int cnt = 0;
    while(scanf("%c", &ch) != EOF) { // EOF = -1，不等于0
        if (ch == '"') {
            printf("%s", (cnt == 0) ? "``" : "''"); // ?:简洁代码
            cnt = !cnt; // 完成0和1转换
        }
        else printf("%c", ch);
    }
    return 0;
}