#include<bits/stdc++.h>
using namespace std;
int num[10] = {0};
int main() {
    int T, n;
    string s;
    scanf("%d", &T);
    while(T --) {
        scanf("%d", &n);
        fill(num, num + 10, 0);
        for (int i = 1; i <= n; i ++) {
            s = to_string(i);
            for (auto ch : s) num[ch - '0'] ++;
        }
        for (int i = 0; i < 10; i ++) {
            printf("%d%s", num[i], (i == 9) ? "\n" : " ");
        }
    }
    return 0;
}